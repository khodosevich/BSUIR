using Common;
using Common.Coders;
using System.Text;

namespace Writer
{
    public class WriterPort : PortWrapper
    {
        public WriterPort(string portName,int  speed) : base(portName, speed)
        {
        }

        public void WriteProccess()
        {
            base.PortInfo();

            BitstuffCoder coder = new BitstuffCoder();

            while (true)
            {
                var data = Console.ReadLine();

                var bytes = Encoding.ASCII.GetBytes(data);

                var valueBytes = bytes.Append((byte)0).ToArray();

                var stuffedValue = coder.Encode(BaseCoder.Decode(valueBytes));

                var package = DataPackageOperations.Configure(stuffedValue);

                var dataToSend = package.Serialize();

                _serialPort.Write(dataToSend, 0, dataToSend.Length);
            }
        }
    }
}
