package Demo

import scala.io.StdIn

object Conditions {
  def main(args: Array[String]):Unit = {

    println("enter your age: ")
    var age = StdIn.readInt();

    var res = 0;

    if(age < 18 ) {
      println("your age is less than 18")
      res = 1
    } else if (age >= 30 || age > 18) {
      println("your age is  18...30")
      res = 2
    } else {
      println("30+")
      res = 3
    }
  }

  //funct style
  val result = if(5==5 ){
    5
  }else{
    3
  }

  println(result)

}
