﻿using UnityEngine;
using System.Collections.Generic;
using System.IO;
using System.Net.Sockets;
using System.Text;
using System.Threading;

public class InputController
{
    public float Currenth = 0;
    public float Currentt = 0;
    public bool ish = true;

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

                if (read == 13)
                {
                    // Once we have a reading, convert our buffer to a string, since the values are coming as strings
                    var str = Encoding.ASCII.GetString(buffer.ToArray());

                    // We assume that they're floats
                    var val = float.Parse(str);

                    if (ish == true)
                    {
                        Currenth = val;
                        ish = false;
                    }
                    else
                    {
                        Currentt = val;
                        ish = true;
                    }

                    buffer.Clear();
                }
                else
                    buffer.Add((byte)read);
                
            }

        });
        thread.Start();
    }
}