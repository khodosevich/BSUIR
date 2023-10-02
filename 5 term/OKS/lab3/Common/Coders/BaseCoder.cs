using System.Collections;
using System.Text;

namespace Common.Coders
{
    public static class BaseCoder
    {

        public static string BitsToString(BitArray bitArray)
        {
            var result = string.Empty;
            foreach (var bit in bitArray)
                result += (bool)bit == true ? "1" : "0";
            return result;
        }

        public static BitArray StringToBits(string text)
        {
            var bitArray = new BitArray(text.Length);

            for (int i = 0; i < text.Length; i++)
                bitArray[i] = text[i] == '1';

            return bitArray;
        }

        public static string Decode(byte[] message) => Encoding.ASCII.GetString(message).Trim('\0');

        public static byte[] Encode(string message) => Encoding.ASCII.GetBytes(message);
    }
}
