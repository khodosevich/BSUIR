using Common.Coders;
using System.Collections;

namespace Common.Extensions
{
    public static class BitArrayExtensions
    {
        public static byte[] ToByteArray(this BitArray bitArray)
        {
            var bytes = new byte[(int)Math.Ceiling(bitArray.Length / 8.0)];
            bitArray.CopyTo(bytes, 0);
            return bytes;
        }
    }
}
