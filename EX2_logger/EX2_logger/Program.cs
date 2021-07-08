using System;
using System.Text;
using System.IO;

namespace EX2_logger
{
    enum Severity : byte
    {
        trace,
        debug,
        information,
        warning,
        error,
        critical
    }

    class Logger : IDisposable
    {
        StreamWriter stwr;

        public void Dispose()
        {
            stwr.Dispose();
        }

        public void Log(in string data, in Severity severity)
        {
            stwr.WriteLine(new StringBuilder("[").Append(DateTime.Now).Append("][").Append(severity.ToString()).Append("]: ").Append(data).ToString());
        }

        public Logger(string way)
        {
            stwr = new StreamWriter(way, false, System.Text.Encoding.Default);
        }

    }
    class Program
    {
        static void Main(string[] args)
        {
            Logger a = new Logger(@"A:\Проекты\EX2_logger\EX2_logger\exe.txt");
            a.Log("log", Severity.error);
            a.Dispose();
        }
    }
}