﻿using System.Diagnostics;

namespace lab1
{
    public class Program
    {
        static void Main(string[] args)
        {
            string portNamesPath = $"C:\\Users\\khodosevich\\git\\5 term\\OKS\\lab1\\lab1\\Configuration\\PortPairConfig.csv";

            var portPairs = GettPortNames(portNamesPath);

            int speed = EnterSpeed();

            var processes = StartProcesses(portPairs, speed);

            Console.WriteLine("Enter 'exit' to close ports:");

            var end = string.Empty;

            while(!end.Equals("exit")) 
            {
                end = string.Empty;
                end = Console.ReadLine();
            }

            processes.ForEach(p => p.Kill());
        }

        private static List<(string, string)> GettPortNames(string configFileName)
        {
            var portNames = new List<(string, string)>();

            if (File.Exists(configFileName))
            {
                string[] lines = File.ReadAllLines(configFileName);

                foreach (string line in lines)
                {
                    string[] ports = line.Split(',');
                    if (ports.Length == 2)
                    {
                        string port1 = ports[0].Trim();
                        string port2 = ports[1].Trim();

                        portNames.Add((port1, port2));
                    }
                }
            }

            return portNames;
        }

        private static Process StartReader(string portName, int speed)
        {
            var p = new Process();
            
            p.StartInfo.FileName = $"C:\\Users\\khodosevich\\git\\5 term\\OKS\\lab1\\Reader\\bin\\Debug\\net7.0\\Reader.exe";
            p.StartInfo.UseShellExecute = true;
            p.StartInfo.Arguments = string.Format("{0},{1}", portName, speed);
            p.Start();

            return p;
        }

        private static Process StartWriter(string portName, int speed)
        {
            var p = new Process();
            
            p.StartInfo.FileName = $"C:\\Users\\khodosevich\\git\\5 term\\OKS\\lab1\\Writer\\bin\\Debug\\net7.0\\Writer.exe";
            p.StartInfo.UseShellExecute = true;
            p.StartInfo.Arguments = string.Format("{0},{1}", portName, speed);
            p.Start();

            return p;            
        }

        private static int EnterSpeed() 
        {
            int speed;
            try
            {
                Console.WriteLine("Choose a speed:");
                speed = int.Parse(Console.ReadLine());

                if (speed < 0) 
                {
                    speed = speed * (-1);
                }
            } 
            catch 
            {
                Console.WriteLine("Bad speed");
                speed = EnterSpeed();
            }

            return speed;
        }

        private static List<Process> StartProcesses(List<(string, string)> portPairs, int speed = 19200) 
        {
            List<Process> processes = new List<Process>();

            foreach (var portPair in portPairs)
            {
                processes.Add(StartReader(portPair.Item1, speed));
                processes.Add(StartWriter(portPair.Item2, speed));
            }

            return processes;
        } 
    }
}