using Common;
using Common.Coders;
using System.Collections;
using System.IO.Ports;

namespace Reader
{
    internal class ReaderPort : PortWrapper
    {
        BitstuffCoder coder;
        public ReaderPort(string portName, int speed) : base(portName, speed)
        {
            _serialPort.DataReceived += new SerialDataReceivedEventHandler(Output);
            coder = new BitstuffCoder();
        }

        public void ReadProccess()
        {
            base.PortInfo();

            while (true) ;
        }

        private void Output(object sender, SerialDataReceivedEventArgs e)
        {
            var buffer = new byte[1024];
            var readed = _serialPort.Read(buffer, 0, 1024);

            int startIndex = -1;
            for (int i = 0; i < readed; i++)
            {
                if (buffer[i] == DataPackageOperations.GetStartFlag())
                {
                    startIndex = i;
                    break;
                }
            }

            if (startIndex >= 0)
            {
                ArraySegment<byte> segment = new ArraySegment<byte>(buffer, startIndex, buffer.Length - startIndex);

                DataPackage receivedPackage = new DataPackage();
                if (receivedPackage.Deserialize(segment.ToArray()))
                {
                    var message = coder.Decode(receivedPackage.Data);
                    Console.WriteLine(message);
                    var messageBytes = BaseCoder.Encode(message);

                    Console.WriteLine("Data before stuff: " + BaseCoder.BitsToString(new BitArray(receivedPackage.Data)));
                    Console.WriteLine("Data after stuff:  " + BaseCoder.BitsToString(new BitArray(messageBytes)));
                    Console.WriteLine($"{receivedPackage.Length} bytse received");

                }
            }
        }
    }
}