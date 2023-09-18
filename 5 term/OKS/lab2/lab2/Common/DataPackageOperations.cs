namespace Common
{
    public static class DataPackageOperations
    {
        public static DataPackage Configure(byte[] data) 
        {
            return new DataPackage
            {
                Flag = GetStartFlag(),
                DestinationAddress = 0,
                SourceAddress = 0,
                Length = data.Length,
                Data = data,
                Fcs = 0
            };
        }

        public static byte GetStartFlag() 
        {
            return 'h' + 14;
        }
    }
}
