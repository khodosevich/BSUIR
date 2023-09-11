package Demo

import scala.annotation.tailrec

object AlternativeBasicLoops {

  def fact( n :Int ):BigInt ={
    assert(n >= 0, "ожидается  number > 0")
    assert(n < 50000, "слишком большое число")

    @tailrec
    def f(n:Int, acc : BigInt = 1):BigInt =
      if(n > 0) f(n - 1 , acc * n)
      else acc

    f(n)
  }

  def fact1( n : Int) = {
    assert(n >= 0, "ожидается  number > 0")
    assert(n < 50000, "слишком большое число")

    if (n == 0) 1
    else (1 to n).foldLeft(BigInt(1)) ( _ * _ )
  }

  def fact2(n: Int) = {
    assert(n >= 0, "ожидается  number > 0")
    assert(n < 50000, "слишком большое число")

    if (n == 0) 1
//    else (BigInt(1) to BigInt(n)).reduce(_ * _)
    else (BigInt(1) to BigInt(n)).product
  }

  def main(args: Array[String]): Unit = {
     println(fact(5))
     println(fact1(5))
     println(fact2(5))
  }

}
