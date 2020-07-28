using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace ChattingClient
{
    internal class MySocket
    {
        public void Init()
        {
            TcpClient tc = new TcpClient("127.0.0.1", 32000);

            NetworkStream stream = tc.GetStream();
            string msg = "hello world!";
            byte[] buff = Encoding.ASCII.GetBytes(msg);
            stream.Write(buff, 0, buff.Length);

            stream.Close();
            tc.Close();
        }
    }
}