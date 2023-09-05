package Demo

import scala.io.StdIn

object LoopWhile {

  def fact(n: Int ) = {
    assert(n > 0, "ожидается  number > 0")
    assert(n < 50000 , "слишком большое число")
    var a = 1;

    var result: BigInt = 1

    while (a <= n) {
      result *= a
      a += 1
    }

    println(result)
    println(result.toString.length)
  }

  def main(args: Array[String]): Unit = {
   fact(5);

    var name = ""
    do{
      name = StdIn.readLine("Enter name: ");
    }while(name.length < 2)


  }
}
