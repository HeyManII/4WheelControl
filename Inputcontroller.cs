using UnityEngine;
using System.Collections.Generic;
using System.IO;
using System.Net.Sockets;
using System.Text;
using System.Threading;
 
public class InputController
{
  public float CurrentValue;
 
  public void Begin(string ipAddress, int port)
  {
    // Give the network stuff its own special thread
    var thread = new Thread(() =>
    {
      // This class makes it super easy to do network stuff
      var client = new TcpClient();
 
      // Change this to your devices real address
      client.Connect(ipAddress, port);
      var stream = new StreamReader(client.GetStream());
 
      // We'll read values and buffer them up in here
      var buffer = new List<byte>();
      while (client.Connected)
      {
        // Read the next byte
        var read = stream.Read();

          // Once we have a reading, convert our buffer to a string, since the values are coming as strings
          var str = Encoding.ASCII.GetString(buffer.ToArray());

          // We assume that they're floats
          var CurrentValue = read.ToString();
       }

    });  
    thread.Start();
  }
}