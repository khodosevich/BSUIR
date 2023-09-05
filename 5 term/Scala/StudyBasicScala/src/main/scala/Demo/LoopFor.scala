package Demo

object LoopFor {

  def main(args: Array[String]):Unit = {
    for(i <-0 until  5){
      println(i)
    }

    for(i <- 0 to (10,2)) println(i)


    val people = List(
      "Bill",
      "Candy",
      "Karen",
      "Leo",
      "Regina"
    )

    for(i <- people) println(i)

    val col1 = List('a','b','c')
    val col2 = List(1,2,3,4)

    for(v1 <- col1; v2<-col2) println(s"$v1 - $v2")

    val resultLoops =
      for {
        v1 <- col1 if v1 > 'a'
        v = v1.toInt
        col3 = col2 map(_ * v)
        v2 <- col3 if v2 < v * 3
      } yield s"$v1 - $v2"

    println(resultLoops)



  }

}
