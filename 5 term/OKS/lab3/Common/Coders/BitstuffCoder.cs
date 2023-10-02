using Common.Extensions;
using System.Collections;
using System.Text;

namespace Common.Coders
{
    public class BitstuffCoder
    {
        private const string beforeBitstuff = "0010000";
        private const string afterBitstuff = "00100000";

        public string Decode(byte[] message)
        {
            var bitString = BaseCoder.BitsToString(new BitArray(message));

            var unbitstuffedString = bitString.Replace(afterBitstuff, beforeBitstuff);

            var unbitstuffedBytes = BaseCoder.StringToBits(unbitstuffedString).ToByteArray();

            return Encoding.ASCII.GetString(unbitstuffedBytes).Trim('\0');
        }

        public byte[] Encode(string message)
        {
            var bytes = Encoding.Default.GetBytes(message);

            var bitString = BaseCoder.BitsToString(new BitArray(bytes));

            var bitsuffedString = bitString.Replace(beforeBitstuff, afterBitstuff);

            var bitsuffedBytes = BaseCoder.StringToBits(bitsuffedString).ToByteArray();

            return bitsuffedBytes;
        }
    }
}
