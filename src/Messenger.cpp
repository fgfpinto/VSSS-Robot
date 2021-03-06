#include <string>
#include "Messenger.h"
#include "PIN_MAP.h"

using std::string;

void Messenger::send_msg(string msg, uint16_t addr) {
	XBeeLib::RemoteXBee802 remoteDevice = XBeeLib::RemoteXBee802(addr);
	xbee->send_data(remoteDevice, (const uint8_t *) msg.c_str(), (uint16_t ) msg.size(), false);
}

template<int size>
msg_data<size> Messenger::get_values(const string &msg, unsigned int first_char_pos) {
	std::array<float,size> values{};
	unsigned int pos_atual = first_char_pos;
	for (int i = 0; i < size; ++i) {
		size_t delim_pos = msg.find(';', pos_atual);
		if (delim_pos == string::npos && i != size - 1) return {values,false};
		values[i] = std::stof(msg.substr(pos_atual, delim_pos - pos_atual));
		pos_atual = delim_pos + 1;
	}
	return {values,true};
}

void Messenger::Update_PID_Pos(string msg) {
	msg_data<2> values = get_values<2>(msg, 2);
	if(values.is_valid) {
		robot->kgz = values[0];
		robot->set_max_theta_error(values[1]);
	}
}

void Messenger::Update_PID_K(string msg) {
	msg_data<3> values = get_values<3>(msg, 1);
	if(values.is_valid)
		robot->controller.set_pid_constants(values[0], values[1], values[2]);
}

void Messenger::uvf_message(std::string &msg) {
	msg_data<6> values = get_values<6>(msg, 1);
	if(values.is_valid)
		robot->start_uvf_control(values[0], values[1], values[2], values[3], values[4], values[5], true);
}

void Messenger::GoToPoint(string msg) {
	msg_data<3> values = get_values<3>(msg, 1);
	if(values.is_valid)
		robot->start_position_control(values[0], values[1], values[2]);
}

void Messenger::GoToVector(string msg) {
	msg_data<2> values = get_values<2>(msg, 1);
	if(values.is_valid)
		robot->start_vector_control(values[0], values[1]);
}

void Messenger::Update_ACC(string msg) {
	msg_data<1> values = get_values<1>(msg, 1);
	if(values.is_valid)
		robot->acc_rate = values[0];
}

void Messenger::goToOrientation(string msg) {
	msg_data<2> values = get_values<2>(msg, 1);
	if(values.is_valid)
		robot->start_orientation_control(values[0], values[1]);
}

string Messenger::decode_strings(string msg) {
	size_t id_pos, end_pos;
	if ((id_pos = msg.find(ID)) == string::npos ||
		(end_pos = msg.find('#', id_pos)) == string::npos)
		return "";
	else return msg.substr(id_pos + 2, end_pos - id_pos - 2);
}

void Messenger::send_battery() {
	AnalogIn vin_all_cells(ALL_CELLS);
	float vbat = vin_all_cells.read() * (3.3f * 1470.0f/470.0f);
	float vbat_round = std::round(vbat*1000)/1000;
	string msg_bat = "B" + std::to_string(vbat_round);
	send_msg(msg_bat);
}

void Messenger::decode_msg(string msg) {
	if (msg[1] == '@') {
		string s = decode_strings(msg);
		if (!s.empty()) msg = s;
		else return;
	}

	switch (msg[0]) {
		case 'U':
			uvf_message(msg);
			return;
		case 'K':
			if(msg[1] == 'P') Update_PID_Pos(msg);
			else Update_PID_K(msg);
			return;
		case 'A':
			Update_ACC(msg);
			return;
		case 'O':
			goToOrientation(msg);
			return;
		case 'P':
			GoToPoint(msg);
			return;
		case 'V':
			GoToVector(msg);
			return;
		case 'D':
			debug_mode = !debug_mode;
//			(*r).controllerA->debug_mode = debug_mode;
//			(*r).controllerB->debug_mode = debug_mode;
			return;
		case 'B':
			send_battery();
			return;
		default:
			break;
	}

	msg_data<2> values = get_values<2>(msg, 0);
	if(values.is_valid)
		robot->start_velocity_control(values[1], values[0]);
}

Messenger::Messenger(char id, Robot *robot, XBeeLib::XBee802 *this_xbee) {
	setlocale(LC_ALL, "C");
	xbee = this_xbee;
	debug_mode = false;
	this->robot = robot;
	ID = id;
}
