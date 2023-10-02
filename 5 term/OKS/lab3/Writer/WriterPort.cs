using Common;
using Common.Coders;
using Common.Extensions;
using System.Collections;
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

            BitstuffCoder _bitstuffCoder = new BitstuffCoder();

            while (true)
            {
                var data = Console.ReadLine();

                var bytes = Encoding.ASCII.GetBytes(data);

                var valueBytes = bytes.Append((byte)0).ToArray();

                var stuffedValue = _bitstuffCoder.Encode(BaseCoder.Decode(valueBytes));

                var hamingValue = HammingCoder.Encode(stuffedValue);

                var package = DataPackageOperations.Configure(hamingValue);

                var dataToSend = package.Serialize();

                _serialPort.Write(dataToSend, 0, dataToSend.Length);
            }
        }
    }
}
