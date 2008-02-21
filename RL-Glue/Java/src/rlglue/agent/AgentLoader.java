/* 
* Copyright (C) 2007, Brian Tanner
* 
http://rl-glue.googlecode.com/

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

package rlglue.agent;
import rlglue.network.Network;

public class AgentLoader
{
	public static void main(String [] args) throws Exception
	{
		String usage = "java AgentLoader <Agent> -classpath <Path To RLGlue>";

		String envVars = "The following environment variables are used by the agent to control its function:\n" + 
		"RLGLUE_HOST  : If set the agent will use this ip or hostname to connect to rather than " + Network.kDefaultHost + "\n" + 
		"RLGLUE_PORT  : If set the agent will use this port to connect on rather than " + Network.kDefaultPort + "\n" +
		"RLGLUE_AUTORECONNECT  : If set the agent will reconnect to the glue after an experiment has finished\n";

		if (args.length < 1) {
			System.out.println(usage);
			System.out.println(envVars);
			System.exit(1);
		}

		Agent agent = (Agent)Class.forName(args[0]).newInstance();
		ClientAgent client = new ClientAgent(agent);
		int autoReconnect = 0;

		String host = Network.kDefaultHost;
		int port = Network.kDefaultPort;

		String hostString = System.getenv("RLGLUE_HOST");
		String portString = System.getenv("RLGLUE_PORT");
		String reconnect = System.getenv("RLGLUE_AUTORECONNECT");

		if (hostString != null)
			host = hostString;

		try {
			port = Integer.parseInt(portString);
		}
		catch (Exception e) {
			port = Network.kDefaultPort;
		}

		try {
			autoReconnect = Integer.parseInt(reconnect);
		}
		catch (Exception e) {
			autoReconnect = 0;
		}

		System.out.print("Connecting to " + host + " on port " + port + "...");

		do {
			client.connect(host, port, Network.kRetryTimeout);
			System.out.println("Connected");
			client.runAgentEventLoop();
			client.close();
		} while (autoReconnect == 1);
	}
}
