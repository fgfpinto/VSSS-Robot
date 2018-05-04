set(XBEELIB_SRC
	${LIB_DIR}/XBeeLib/DigiLogger/DigiLogger.cpp
	${LIB_DIR}/XBeeLib/DigiLogger/DigiLoggerMbedSerial.cpp
	${LIB_DIR}/XBeeLib/FrameBuffer/FrameBuffer.cpp
	${LIB_DIR}/XBeeLib/FrameHandlers/FH_AtCmdResp.cpp
	${LIB_DIR}/XBeeLib/FrameHandlers/FH_IoDataSample802.cpp
	${LIB_DIR}/XBeeLib/FrameHandlers/FH_IoDataSampleDM.cpp
	${LIB_DIR}/XBeeLib/FrameHandlers/FH_IoDataSampleZB.cpp
	${LIB_DIR}/XBeeLib/FrameHandlers/FH_ModemStatus.cpp
	${LIB_DIR}/XBeeLib/FrameHandlers/FH_RxPacket802.cpp
	${LIB_DIR}/XBeeLib/FrameHandlers/FH_RxPacketDM.cpp
	${LIB_DIR}/XBeeLib/FrameHandlers/FH_RxPacketZB.cpp
	${LIB_DIR}/XBeeLib/FrameHandlers/FrameHandler.cpp
	${LIB_DIR}/XBeeLib/Frames/802_Frames.cpp
	${LIB_DIR}/XBeeLib/Frames/ApiFrame.cpp
	${LIB_DIR}/XBeeLib/Frames/AtCmdFrame.cpp
	${LIB_DIR}/XBeeLib/Frames/DigiMeshFrames.cpp
	${LIB_DIR}/XBeeLib/Frames/ZigbeeFrames.cpp
	${LIB_DIR}/XBeeLib/IO/IOSample802.cpp
	${LIB_DIR}/XBeeLib/IO/IOSampleDM.cpp
	${LIB_DIR}/XBeeLib/IO/IOSampleZB.cpp
	${LIB_DIR}/XBeeLib/RemoteXBee/RemoteXBee.cpp
	${LIB_DIR}/XBeeLib/Utils/Utils.cpp
	${LIB_DIR}/XBeeLib/XBee/AtCommands.cpp
	${LIB_DIR}/XBeeLib/XBee/RadioConfig.cpp
	${LIB_DIR}/XBeeLib/XBee/XBee.cpp
	${LIB_DIR}/XBeeLib/XBee802/XBee802.cpp
	${LIB_DIR}/XBeeLib/XBeeDM/XBeeDM.cpp
	${LIB_DIR}/XBeeLib/XBeeZB/XBeeZB.cpp)

set(XBEELIB_DIR
	${LIB_DIR}/XBeeLib
	${LIB_DIR}/XBeeLib/DigiLogger
	${LIB_DIR}/XBeeLib/FrameBuffer
	${LIB_DIR}/XBeeLib/FrameHandlers
	${LIB_DIR}/XBeeLib/Frames
	${LIB_DIR}/XBeeLib/IO
	${LIB_DIR}/XBeeLib/RemoteXBee
	${LIB_DIR}/XBeeLib/Utils
	${LIB_DIR}/XBeeLib/XBee
	${LIB_DIR}/XBeeLib/XBee802
	${LIB_DIR}/XBeeLib/XBeeDM
	${LIB_DIR}/XBeeLib/XBeeZB)
