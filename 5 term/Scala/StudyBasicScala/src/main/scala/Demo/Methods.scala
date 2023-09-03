package Demo

object Methods {

  def max (x : Int, y : Int): Int = {
    if(x > y ) x else y
  }

  val max1 : (Int,Int) => Int = (a,b) => a+b



  def main(args: Array[String]): Unit = {
    println(max(7,5));
    println(max1(7,7));
  }

}
