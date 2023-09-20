object Main {

    def double(x: Int): Int = x * 2

    def isEven(x: Int): Boolean = x % 2 == 0


    def sumList(lst: List[Int]): Int = {
      if (lst.isEmpty) 0
      else lst.head * lst.head + sumList(lst.tail)
    }


  def main(args: Array[String]): Unit = {
      val myList = List(1, 2, 3, 4, 5)
      val doubledList = myList.map( double )
//      println(doubledList)

//      println(myList.mkString(", "))
//
//          val filteredList = myList.filter(isEven)
//          println(filteredList.mkString(", "))

//      val sum = myList.foldLeft(0)((ac_c, x) => ac_c + x)
//      println(sum) // Output: 15

//      val a = List(1, 2, 3)
//      val b = List("one", "two", "three")
//      val zipped = a.zip(b)
//
//      println(zipped)

//      val numbers = List(1, 2, 3, 4, 5)
//      val first = numbers.head
//      val rest = numbers.tail
//
//      println(first)
//      println(rest)


//      val sumw = sumList(myList)
//      println(sumw)


    println(myList.reverse)
  }

}