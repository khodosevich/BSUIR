package Demo

object Functions {

   val func = (x : Int) => {
      println(x)
      x * x
   }

   val add : (Int,Int) => Int = _ + _
   val add1 = (_ : Int) + (_ : Int)

   val sqr = ( x : Int ) => x * x

   val factorial: Int => Int =
      n => if (n == 0) 1 else n * factorial(n - 1)

   val addSqr = ( x :Int , y : Int ) => {

      val q = ( q : Int ) => q * q

      val v1 = sqr(x)
      val v2 = q(y)

      add(v1,v2)
   }

   def main(args: Array[String]): Unit = {
      println(func(3))

      println(func.isInstanceOf[Any])
      println(func.isInstanceOf[AnyRef])

      println(add(6,5))
      println(add1(6,9))

      println(factorial(5))

      println(addSqr(2,3))

      //      println(func.isInstanceOf[AnyVal])
   }

}

