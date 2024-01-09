using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSconApp01
{
    internal class Program  //program은 바꾸는 것이 아님 (주 진입점이라서)
    {
        static void Main(string[] args)
        {
            Test test = new Test();
            test.Main();
        }
    }
    class Test
    {
        void func1()
        {
            Console.WriteLine("double type의 크기 " + sizeof(double) + "범위 " + double.MinValue + ", " + double.MaxValue);
            Console.WriteLine("long type의 크기 " + sizeof(long) + "범위 " + long.MinValue + ", " + long.MaxValue);
            Console.WriteLine("float type의 크기 " + sizeof(float) + "범위 " + float.MinValue + ", " + float.MaxValue);
        }
          
        void func2()
        {
            char a = 'A';
            Console.WriteLine("char a = " + a);
            Console.WriteLine("char a + 1 = " + (a + 1));
            Console.WriteLine("char a + 2 = " + (a + 2));
            Console.ReadKey();
        }

        void func3()
        {
            var a = 20; //string type으로 이해
            Console.WriteLine($"ASCII code '1' = \x31 \u0031"); // 49 = '1'
            a = 10;
            Console.WriteLine($"var a = {a}");
            Object o = a;
            Console.WriteLine($"Object o = {o}");
            o = "문자열도 되나요?";
            Console.WriteLine($"Object o = {o}");
            string s = (string)o; //casting 객체 사용
            Console.WriteLine($"string s = {s}");
        }

        void func4() 
        {
            char[] arr = { '안','녕','하','세','요' };
            char a1 = arr[0];

            
            for(int i = 0; i < arr.Length; i++)
            {
                Console.Write(arr[i]);
            }
            Console.WriteLine("");
            string s = new string(arr); Console.WriteLine(s); //string 오직 문자열을 처리하기 위한 클래스
            s = new string(arr,1,2); Console.WriteLine(s);
        }
        public void Main()
        {
            //Console.WriteLine("int type의 크기 " + sizeof(int) + "범위 " + int.MinValue + ", " + int.MaxValue);
            //Console.WriteLine("(표준) int type의 크기 {0} 범위 {1},{2}", sizeof(int), int.MinValue, int.MaxValue);
            //Console.WriteLine($"(보간) int type의 크기 {sizeof(int)} 범위 {int.MinValue},{int.MaxValue}");
            //func1(); func2(); func3();
            func3();
            Console.ReadKey();
        }
    }
}
