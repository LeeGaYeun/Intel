
class Calculator:
    class FourCal:
        def __init__(self, a, b):
            self.fisrt = a
            self.second = b
            self.result = 0
        def setdata(self, a, b):
            self.first = a
            self.second = b
       
        def add(self):
            self.result = self.first + self.second
            return self.result
        
        def sub(self):
            self.result = self.first - self.second
            return self.result
        
        def mul(self):
            self.result = self.first * self.second
            return self.result
        
        def div(self):
            self.result = self.first / self.second
            return self.result
        
    class MoreFourCal(FourCal):
        def pow(self):
            self.result = self.first ** self.second#제곱근은 **
            return self.result

    class SafeFourCal(FourCal): # 오버라이딩
        def div(self):
            if self.second == 0:
                return 0
            else:
                return self.first / self.second
    
    a = FourCal(4, 0)
    #print('{0:.2f}'.format(a.div()))

from game import *
echo.echo_test()