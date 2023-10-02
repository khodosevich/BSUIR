using Common.Extensions;
using System.Collections;
using System.Text;

namespace Common.Coders
{
    public static class HammingCoder
    {

        private static int GetCountOfBitsToInsert(int length) => Enumerable.Range(0, length).First(i => length + i < Math.Pow(2, i));

        private static int GetCountOfContainedBits(int length) => Enumerable.Range(0, length).First(i => length - i < Math.Pow(2, i));

        public static List<string> CalculateControlLines(string code)
        {
            var length = GetCountOfContainedBits(code.Length);
            return Enumerable.Range(1, length).Select(i => CalculateControlLine(i, code.Length)).ToList();
        }

        public static string CalculateControlLine(int number, int length)
        {
            var line = string.Empty;
            for (var i = 0; i < length; i++)
            {
                line += ((i + 1) / (int)Math.Pow(2, number - 1) % 2 == 0) ? "0" : "1";
            }

            return line;
        }

        public static List<bool> CalculateControlBits(string controlCode, List<string> controlLines)
        {
            return controlLines.Select(line => CalculateControlBit(controlCode, line)).ToList();
        }

        public static bool CalculateControlBit(string controlCode, string controlLine)
        {
            var res = controlCode.Where((s, i) => s == '1' && controlLine[i] == '1').Count();

            return res % 2 == 1;
        }

        #region Encoding

        public static byte[] Encode(byte[] bytes)
        {
            var bitString = BaseCoder.BitsToString(new BitArray(bytes));

            bitString = InitializeControlBits(bitString); 

            var controlLines = CalculateControlLines(bitString);

            var bits = CalculateControlBits(bitString, controlLines);

            bitString = InsertControlBits(bitString, bits);

            var encodedBytes = BaseCoder.StringToBits(bitString).ToByteArray();

            return encodedBytes;
        }

        public static string InitializeControlBits(string bits)
        {
            var countOfBits = GetCountOfBitsToInsert(bits.Length);

            for (var i = 0; i < countOfBits; i++)
            {
                var n = (int)Math.Pow(2, i) - 1;
                if (n <= bits.Length) bits = bits.Insert(n, "0");
                else bits += "0";
            }

            return bits;
        }

        public static string InsertControlBits(string bitsString, List<bool> bits)
        {
            var chars = bitsString.ToCharArray();

            for (int i = 0; i < bits.Count; i++)
            {
                var n = (int)Math.Pow(2, i) - 1;
                chars[n] = bits[i] ? '1' : '0';
            }

            return new string(chars);
        }

        #endregion

        #region Decoding

        public static string Decode(byte[] message, byte fcs)
        {
            var bitString = BaseCoder.BitsToString(new BitArray(message));

            var controlLines = CalculateControlLines(bitString);

            var sindromBits = CalculateControlBits(bitString, controlLines);


            if (!sindromBits.All(bit => bit == false))
            {
                var fcsBefore = DataPackageOperations.GetFcs(fcs);
                var fcsInMessage = DataPackageOperations.CalculateParitet(bitString);


                if (fcsBefore == fcsInMessage)
                    Console.WriteLine("Double mistake was detected");
                else
                    Console.WriteLine("Single mistake was detected");


                var errorBit = GetErrorBitNumber(sindromBits);
                bitString = FixBit(bitString, errorBit);
                Console.WriteLine("Error bit: " + errorBit);
            }

            var decodedBitsString = ExtractControlBits(bitString);

            var decodedBytes = BaseCoder.StringToBits(decodedBitsString).ToByteArray();

            return BaseCoder.Decode(decodedBytes);
        }

        public static string FixBit(string bitString, int errorBit)
        {
            var bit = bitString[errorBit-1];
            return bitString.Remove(errorBit - 1, 1).Insert(errorBit - 1, bit == '1' ? "0" : "1");
        }

        public static int GetErrorBitNumber(List<bool> bits)
        {
            var res = 0;
            for (int i = 0; i < bits.Count; i++)
            {
                if (bits[i] == true) res += (int)Math.Pow(2, i);
            }
            return res;
        }

        public static string ExtractControlBits(string bitsString)
        {
            var numberOfBits = GetCountOfContainedBits(bitsString.Length);

            for (int i = 0; i < numberOfBits; i++)
            {
                var n = (int)Math.Pow(2, i) - 1;
                bitsString = bitsString.Remove(n - i, 1);
            }

            return bitsString;
        }

        #endregion

        public static string DistortBits(string bitString) 
        {
            Random random = new Random(); 

            var randomValue = random.Next(100);

            Console.WriteLine("Random value: "+ randomValue);

            if(randomValue > 50) 
            {
                var bitNumber = randomValue % bitString.Length;
                if (bitNumber < 2)
                    bitNumber = 2;
                bitString = FixBit(bitString, bitNumber);
                
                if(randomValue > 75)
                    bitString = FixBit(bitString, bitNumber-1);
            }

            return bitString;
        }
    }
}

