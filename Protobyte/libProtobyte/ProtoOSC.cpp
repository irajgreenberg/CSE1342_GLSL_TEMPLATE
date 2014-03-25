/*!  \brief  ProtoOSC.cpp:
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

#include "ProtoOSC.h"

void ProtoOSC::ProcessMessage(const osc::ReceivedMessage& m,
	const IpEndpointName& remoteEndpoint)
{
	(void)remoteEndpoint; // suppress unused parameter warning

	try{
		// example of parsing single messages. osc::OsckPacketListener
		// handles the bundle traversal.

		if (std::strcmp(m.AddressPattern(), "/test1") == 0){
			// example #1 -- argument stream interface
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			bool a1;
			osc::int32 a2;
			float a3;
			const char *a4;
			args >> a1 >> a2 >> a3 >> a4 >> osc::EndMessage;

			std::cout << "received '/test1' message with arguments: "
				<< a1 << " " << a2 << " " << a3 << " " << a4 << "\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/test2") == 0){
			// example #2 -- argument iterator interface, supports
			// reflection for overloaded messages (eg you can call 
			// (*arg)->IsBool() to check if a bool was passed etc).
			osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
			bool a1 = (arg++)->AsBool();
			int a2 = (arg++)->AsInt32();
			float a3 = (arg++)->AsFloat();
			const char *a4 = (arg++)->AsString();
			if (arg != m.ArgumentsEnd())
				throw osc::ExcessArgumentException();

			std::cout << "received '/test2' message with arguments: "
				<< a1 << " " << a2 << " " << a3 << " " << a4 << "\n";
		}
	}
	catch (osc::Exception& e){
		// any parsing errors such as unexpected argument types, or 
		// missing arguments get thrown as exceptions.
		std::cout << "error while parsing message: "
			<< m.AddressPattern() << ": " << e.what() << "\n";
	}
}


