object Variant1 {
  def main(args: Array[String]): Unit = {
    print("Enter the number: ")

    var numberString =""
    var a =0
    var b=0
    var c=0
    var rez: Float =0.0
    var z=0
    numberString = scala.io.StdIn.readLine()
    if ( (numberString.length() <= 10)) {
      println("Incorrect number");
      sys.exit(0)  }

    for (i <- 1 to 10) {
      a = numberString.substring(0, 5).toInt
      //println(numberString.length());

      b=  numberString.substring(5, 10).toInt
      c= a*b
      rez=c.toString().substring(0,3).toFloat / 1000
      z+=c
      println(a);
      println(b);
      println(c);
      println(rez);
      println("z="+ z)
      numberString= numberString.substring(1,numberString.length()-1)
      numberString="011"+z

    }
  }
}


object Variant2  {

  def substringFromSymbolsAtEvenPositions(str: String): String = {
    val result = new StringBuilder
    for (i <- str.indices if i % 2 == 1) {
      result.append(str(i))
    }
    result.toString()
  }

  def substringFromSymbolsAtOddPositions(str: String): String = {
    val result = new StringBuilder
    for (i <- str.indices if i % 2 == 0) {
      result.append(str(i))
    }
    result.toString()
  }

  def main(args: Array[String]): Unit = {

    print("Enter the number: ")

    var numberString = ""
    var a = 0
    var b = 0
    var c = 0
    var rez: Float = 0.0
    var z = 0

    numberString = scala.io.StdIn.readLine()

    if ((numberString.length() < 10)) {
      println("Incorrect number");
      sys.exit(0)
    }

    for (i <- 1 to 10) {
      a = substringFromSymbolsAtEvenPositions(numberString).toInt

      b = substringFromSymbolsAtOddPositions(numberString).toInt
      c = a * b

      rez = c.toString().substring(0, 3).toFloat / 1000

      z += c

      println("\n\n")
      println(a);
      println(b);
      println(c);
      println(rez);
      println("z=" + z)
      println("\n\n")

      numberString = numberString.substring(1, numberString.length() - 1)
      numberString = "011" + z.toString.replaceAll("-", "")

    }
  }
}
