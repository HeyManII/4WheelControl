using UnityEngine;
using System.Collections.Generic;
using System.IO;
using System.Net.Sockets;
using System.Text;
using System.Threading;

public class OutputController
{
	public string clientMessage;

	public TcpClient client;
	public StreamWriter writer; 

    public void Begin(string ipAddress, int port)
    {
        // Give the network stuff its own special thread
        var thread = new Thread(() =>
        {	
        	client  = new TcpClient();
            // Change this to your devices real address
            client.Connect(ipAddress, port);                                           	
        });
        thread.Start();
    }

    public void sendblue()
    {	
        clientMessage = "blue";
        writer = new StreamWriter(client.GetStream()); 				
		// Convert string message to byte array.                 
		//byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(clientMessage); 				
		// Write byte array to socketConnection stream.                 
		writer.Write(clientMessage);               
		Debug.Log("sent blue");
		writer.Flush();
    } 

    public void sendgreen()
    {	
        clientMessage = "green";
        writer = new StreamWriter(client.GetStream()); 				
		// Convert string message to byte array.                 
		//byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(clientMessage); 				
		// Write byte array to socketConnection stream.                 
		writer.Write(clientMessage);               
		Debug.Log("sent green");
		writer.Flush();
    } 

    public void sendred()
    {	
        clientMessage = "red";
        writer = new StreamWriter(client.GetStream()); 				
		// Convert string message to byte array.                 
		//byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(clientMessage); 				
		// Write byte array to socketConnection stream.                 
		writer.Write(clientMessage);               
		Debug.Log("sent red");
		writer.Flush();
    } 

}

    /*public void sendblue()
            {
            	clientMessage = "blue"; 				
				// Convert string message to byte array.                 
				//byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(clientMessage); 				
				// Write byte array to socketConnection stream.                 
				writer.Write(clientMessage);               
				Debug.Log("sent blue");
				writer.Flush();
            }*/

    			/*public void sendgreen()
    			{
    				clientMessage = "green"; 				
					// Convert string message to byte array.                 
					//byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(clientMessage); 				
					// Write byte array to socketConnection stream.                 
					writer.Write(clientMessage);               
					Debug.Log("sent green");
					writer.Flush();
    			}

    			public void sendred()
    			{
    				clientMessage = "red"; 				
					// Convert string message to byte array.                 
					//byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(clientMessage); 				
					// Write byte array to socketConnection stream.                 
					writer.Write(clientMessage);               
					Debug.Log("sent red");
					writer.Flush();
    			}*/