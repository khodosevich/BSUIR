using Common.Coders;
using System.Collections;
using System.IO.Ports;
using System.Text;

namespace Common
{
    public class DataPackage
    {
        public byte Flag { get; set; }
        public int DestinationAddress { get; set; }
        public int SourceAddress { get; set; }
        public int Length { get; set; }
        public byte[] Data { get; set; }
        public byte Fcs { get; set; }

        public byte[] Serialize() 
        {
            List<byte> frame = new List<byte>
            {
                Flag
            };

            frame.AddRange(BitConverter.GetBytes(DestinationAddress));
            frame.AddRange(BitConverter.GetBytes(SourceAddress));
            frame.AddRange(BitConverter.GetBytes(Length));
            frame.AddRange(Data);
            frame.Add(Fcs);

            return frame.ToArray();
        }

        public bool Deserialize(byte[] data) 
        {
            if (data == null || data.Length < 14) 
            {
                return false;
            }

            Flag = data[0];
            DestinationAddress = BitConverter.ToInt32(data, 1);
            SourceAddress = BitConverter.ToInt32(data, 5);
            Length = BitConverter.ToInt32(data, 9);
            Data = new byte[Length];
            Array.Copy(data, 13, Data, 0, Length);
            Fcs = data[Length + 13];

            return true;
        }

    }
}
