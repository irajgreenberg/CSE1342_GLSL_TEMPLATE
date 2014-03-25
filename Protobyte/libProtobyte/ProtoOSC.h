/*!  \brief  ProtoOSC.h:
Simple OSC Send/receive implementation
utilizing oscpack_1_1_0
Protobyte Library v02

Created by Ira on 3/23/14.
Copyright (c) 2014 Ira Greenberg. All rights reserved.

Library Usage:
This work is licensed under the Creative Commons
Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit
http://creativecommons.org/licenses/by-nc-sa/3.0/
or send a letter to Creative Commons,
444 Castro Street, Suite 900,
Mountain View, California, 94041, USA.

This notice must be retained any source distribution.

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#include <iostream>
#include <cstring>
#include <stdlib.h>

#if defined(__BORLANDC__) // workaround for BCB4 release build intrinsics bug
namespace std {
	using ::__strcmp__;  // avoid error: E2316 '__strcmp__' is not a member of 'std'.
}
#endif


#include "OscReceivedElements.h"
#include "OscPacketListener.h"
#include "UdpSocket.h"

#define PORT 7000
class ProtoOSC : public osc::OscPacketListener {
	/*
	Example of two different ways to process received OSC messages using oscpack.
	Receives the messages from the SimpleSend.cpp example.
	*/
protected:
	virtual void ProcessMessage(const osc::ReceivedMessage& m,
		const IpEndpointName& remoteEndpoint);
};

//int main(int argc, char* argv[])
//{
//	(void)argc; // suppress unused parameter warnings
//	(void)argv; // suppress unused parameter warnings

//	ExamplePacketListener listener;
//	UdpListeningReceiveSocket s(
//		IpEndpointName(IpEndpointName::ANY_ADDRESS, PORT),
//		&listener);

//	std::cout << "press ctrl-c to end\n";

//	s.RunUntilSigInt();

//	return 0;
//}
