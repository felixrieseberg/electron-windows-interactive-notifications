using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace InteractiveSharp
{
    class Program
    {

        static void Main(string[] args)
        {
        }
    }

    static class InteractiveNotifications
    {
        [DllImport("InteractiveNotifications.dll")]
        void Register();
    }
}
