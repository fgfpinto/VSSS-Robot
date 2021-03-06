#include <cmath>
#include "Robot.h"
#include "PIN_MAP.h"

#define PI 3.1415926f
#define ROBOT_LOOP_MS 10

Robot::Robot(Messenger *msgr) {
	messenger = msgr;
	state.command = NO_CONTROL;
}

void Robot::start_thread() {
	controller.start_thread();
	control_thread.start(callback(this, &Robot::control_loop));
}

void Robot::control_loop() {
	while(true) {
		if(msg_timeout_timer.read_ms() > msg_timeout_limit) stop_and_wait();
		if(state.command != NO_CONTROL) update_odometry();

		switch (state.command) {
			case UVF_CONTROL:
				uvf_control();
				break;
			case VECTOR_CONTROL:
				vector_control();
				break;
			case POSITION_CONTROL:
				position_control();
				break;
			case ORIENTATION_CONTROL:
				orientation_control();
				break;
			case NO_CONTROL:
//				Robot não faz nada, controle de velocidade é feito em Controller
				break;
			default:
				break;
		}
		Thread::wait(ROBOT_LOOP_MS);
	}
}

void Robot::uvf_control() {
	if(vel_acelerada < 0.3) vel_acelerada = 0.3;
	if(target.velocity == 0) {
		stop_and_wait();
		return;
	}

//	Computes uni-vector field target theta
	float state_to_targ = std::atan2(target.y - state.y, target.x - state.x);
	float state_to_ref = std::atan2(target.ref_y - state.y, target.ref_x - state.x);
	float fi = round_angle(state_to_ref - state_to_targ);
	float uvf_target_theta = round_angle(state_to_targ - uvf_n * fi);

//	Activates backwards movement if theta_error > PI/2
	float theta = state.theta;
	bool move_backwards = std::abs(uvf_target_theta - theta) > PI/2;
	if(move_backwards) theta = round_angle(state.theta + PI);
	if(move_backwards != previously_backwards) vel_acelerada = 0.3;
	previously_backwards = move_backwards;

	float theta_error = round_angle(uvf_target_theta - theta);

//	Decreases velocity for big errors
	if (std::abs(theta_error) > max_theta_error) {
		vel_acelerada = vel_acelerada - 2 * acc_rate * ROBOT_LOOP_MS/1000.0f;
	} else {
//		Applies acceleration until robot reaches target velocity
		if (vel_acelerada < target.velocity) {
			vel_acelerada = vel_acelerada + acc_rate * ROBOT_LOOP_MS/1000.0f;
		} else {
			vel_acelerada = target.velocity;
		}
	}

	set_wheel_velocity_nonlinear_controller(theta_error, vel_acelerada, move_backwards);
}

void Robot::vector_control() {
	if(vel_acelerada < 0.3) vel_acelerada = 0.3;
	if(target.velocity == 0) {
		stop_and_wait();
		return;
	}

	float theta = state.theta;

//	Computes target.theta in direction of {target.x, target.y} before each control loop
	target.theta = std::atan2(target.y - state.y, target.x - state.x);

//	Activates backwards movement if theta_error > PI/2
	bool move_backwards = std::abs(target.theta - state.theta) > PI/2;
	if(move_backwards) theta = round_angle(state.theta + PI);
	if(move_backwards != previously_backwards) vel_acelerada = 0.3;
	previously_backwards = move_backwards;

	float theta_error = round_angle(target.theta - theta);

//	Decreases velocity for big errors
	if (std::abs(theta_error) > max_theta_error) {
		vel_acelerada = vel_acelerada - 2 * acc_rate * ROBOT_LOOP_MS/1000.0f;
	} else {
//		Applies acceleration until robot reaches target velocity
		if (vel_acelerada < target.velocity) {
			vel_acelerada = vel_acelerada + acc_rate * ROBOT_LOOP_MS/1000.0f;
		} else {
			vel_acelerada = target.velocity;
		}
	}

	set_wheel_velocity_nonlinear_controller(theta_error, vel_acelerada, move_backwards);
}

void Robot::position_control() {
//	Stops after arriving at destination
	float position_error = std::sqrt(std::pow(state.x - target.x, 2.0f) + std::pow(state.y - target.y, 2.0f));
	if(target.velocity == 0 || position_error < 1) {
		stop_and_wait();
		return;
	}

	if(vel_acelerada < 0.3) vel_acelerada = 0.3;

//	Computes target.theta in direction of {target.x, target.y} before each control loop
	target.theta = std::atan2(target.y - state.y, target.x - state.x);
	float theta = state.theta;

//	Activates backwards movement if theta_error > PI/2
	bool move_backwards = round_angle(target.theta - state.theta + PI/2) < 0;
	if(move_backwards != previously_backwards) vel_acelerada = 0.3;
	previously_backwards = move_backwards;
	if(move_backwards) theta = round_angle(state.theta + PI);

	float theta_error = round_angle(target.theta - theta);

//	Decreases velocity for big errors and limits maximum velocity
	if (std::abs(theta_error) > max_theta_error) {
		if(vel_acelerada > 0.8) {
			vel_acelerada = 0.8;
		} else if (vel_acelerada > 0.3) {
			vel_acelerada = vel_acelerada - 2 * acc_rate * ROBOT_LOOP_MS/1000.0f;
		}
	} else {
//		Applies acceleration until robot reaches target velocity
		float velocity_difference = target.velocity - vel_acelerada;
		if (velocity_difference > 0.2) {
			vel_acelerada = vel_acelerada + acc_rate * ROBOT_LOOP_MS/1000.0f;
		} else if(velocity_difference < 0) {
			vel_acelerada = target.velocity;
		}
	}

	float limiar = std::atan2(1.0f, position_error);
	limiar = limiar > 30 ? 30 : limiar;
	if(std::abs(theta_error) < limiar) theta_error = 0;

	set_wheel_velocity_nonlinear_controller(theta_error, vel_acelerada, move_backwards);
}


void Robot::orientation_control() {
	float theta = state.theta;

//	Activates backwards movement if theta_error > PI/2
	if(round_angle(target.theta - state.theta + PI/2) < 0){
		theta = round_angle(state.theta + PI);
	}
	float theta_error = round_angle(target.theta - theta);

//	Stops after arriving at desired orientation
	if(std::abs(theta_error) < 2*PI/180) {
		stop_and_wait();
		return;
	}

//	Wheel velocities are always between 1 and -1
	float right_wheel_velocity = saturate(orientation_Kp * theta_error, 1);
	float left_wheel_velocity = saturate(-orientation_Kp * theta_error, 1);

	controller.set_target_velocity(left_wheel_velocity, right_wheel_velocity, target.velocity);
}

void Robot::set_wheel_velocity_nonlinear_controller(float theta_error, float velocity, bool backwards) {
	float m = 1;
	if(backwards) m = -1;

	float right_wheel_velocity = m + std::sin(theta_error) + m*kgz*std::tan(m*theta_error/2);
	right_wheel_velocity = saturate(right_wheel_velocity,1);

	float left_wheel_velocity = m - std::sin(theta_error) + m*kgz*std::tan(-m*theta_error/2);
	left_wheel_velocity = saturate(left_wheel_velocity,1);

	controller.set_target_velocity(left_wheel_velocity, right_wheel_velocity, velocity);
}

void Robot::update_odometry() {
	wheel& left_wheel = controller.left_wheel;
	wheel& right_wheel = controller.right_wheel;

//	encoder_distance: distance travelled since last odometry update. Is updated on Controller::update_wheel_velocity()
	float distance = (left_wheel.encoder_distance + right_wheel.encoder_distance)/2;

	state.x += distance * std::cos(state.theta);
	state.y += distance * std::sin(state.theta);
	state.theta += (right_wheel.encoder_distance - left_wheel.encoder_distance)/Largura_Robo;
	state.theta = round_angle(state.theta);

	left_wheel.encoder_distance = 0;
	right_wheel.encoder_distance = 0;
}

void Robot::start_uvf_control(float x, float y, float x_ref, float y_ref, float n, float velocity, bool reset) {
	if(reset) reset_state();
	target.x = x;
	target.y = y;
	target.ref_x = x_ref;
	target.ref_y = y_ref;
	uvf_n = n;
	target.velocity = velocity;
	state.command = UVF_CONTROL;
	continue_threads();
}

void Robot::start_vector_control(float theta, float velocity, bool reset) {
	if(reset) reset_state();
//	target.theta is computed before each vector control loop, in direction of {target.x, target.y}
	target.x = 50*std::cos(theta * PI/180);
	target.y = 50*std::sin(theta * PI/180);
	target.velocity = velocity;
	state.command = VECTOR_CONTROL;
	continue_threads();
}

void Robot::start_position_control(float x, float y, float velocity, bool reset) {
	if(reset) reset_state();
	target.x = x;
	target.y = y;
	target.velocity = velocity;
	state.command = POSITION_CONTROL;
	continue_threads();
}

void Robot::start_orientation_control(float theta, float velocity, bool reset) {
	if(reset) reset_state();
	target.theta = round_angle(theta * PI/180);
	target.velocity = velocity;
	state.command = ORIENTATION_CONTROL;
	continue_threads();
}

void Robot::start_velocity_control(float vel_left, float vel_right) {
	state.command = NO_CONTROL;
	controller.set_target_velocity(vel_left, vel_right, 1);
	continue_threads();
}

void Robot::continue_threads() {
	msg_timeout_timer.reset();
	msg_timeout_timer.start();
//	Resumes Robot::control_loop thread
	if(control_thread.get_state() == Thread::WaitingThreadFlag) {
		control_thread.signal_set(CONTINUE_SIGNAL);
	}
//	Resumes Controller::control_loop thread
	controller.continue_thread();
}

void Robot::reset_state() {
	state.x = 0;
	state.y = 0;
	state.theta = 0;
}

void Robot::stop_and_wait() {
//	Flag tells Controller to stop robot and pause thread
	controller.stop = true;
	vel_acelerada = 0;
	state.command = NO_CONTROL;
	if(control_thread.get_state() != Thread::WaitingThreadFlag) {
		Thread::signal_wait(CONTINUE_SIGNAL);
		Thread::signal_clr(CONTINUE_SIGNAL);
	}
}

float Robot::round_angle(float angle) {
	float theta = std::fmod(angle, 2*PI);
	if(theta > PI) theta = theta - 2*PI;
	else if(theta < -PI) theta = theta + 2*PI;
	return theta;
}

float Robot::saturate(float value, float limit) {
	if(value > limit) value = limit;
	if(value < -limit) value = -limit;
	return value;
}

void Robot::set_max_theta_error(float error) {
	max_theta_error = round_angle(error * PI/180);
}
