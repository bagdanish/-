using System;
using System.Collections.Generic;

namespace EX_3
{
    class Cache<T>
    {
        private struct Data
        {
            public Data(T value)
            {
                value_ = value;
                add_time_ = DateTime.Now;
            }

            public DateTime add_time_;
            public T value_;
        }

        private Dictionary<string, Data> _map;
        private TimeSpan _live_time;
        private int _capasity;

        public Cache(TimeSpan time, int max_size)
        {
            _map = new Dictionary<string, Data>();
            _live_time = time;
            _capasity = max_size;
        }

        private void KillCache()
        {
            List<string> list_keys = new List<string>();

            foreach (var i in _map)
            {
                TimeSpan a = -1 * i.Value.add_time_.Subtract(DateTime.Now);
                if (a > _live_time) { list_keys.Add(i.Key); }
            }

            foreach (var i in list_keys)
            {
                _map.Remove(i);
            }
        }

        public void Save(T value)
        {
            KillCache();

            Random x = new Random();
            string key = x.Next(0, _capasity).ToString();
            if (_map.ContainsKey(key)) { throw new ArgumentException($"Key: {key} is already exist!"); }

            if (_map.Count == _capasity)
            {
                DateTime min = DateTime.Now;
                string min_key = new string("");
                foreach (var i in _map)
                {
                    if (i.Value.add_time_ < min) { min = i.Value.add_time_; min_key = i.Key; }
                }

                _map.Remove(min_key);
            }

            _map.Add(key, new Data(value));
        }

        public T Get(string key)
        {
            KillCache();

            if (!_map.ContainsKey(key)) { throw new KeyNotFoundException($"Key: {key} is not exist!"); }

            return _map[key].value_;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Cache<int> a = new Cache<int>(TimeSpan.FromSeconds(10), 20);

            try
            {
                a.Save(200);
                a.Save(300);
                a.Save(400);

                a.Get("1");
            }
            catch (KeyNotFoundException ex)
            {
                Console.WriteLine("{0}: {1}", ex.GetType().Name, ex.Message);
            }
            catch (ArgumentException ex)
            {
                Console.WriteLine("{0}: {1}", ex.GetType().Name, ex.Message);
            }
        }
    }
}
