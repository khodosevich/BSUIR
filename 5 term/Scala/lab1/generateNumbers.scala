
import scala.util.Random

object Variant1 {
  def main(args: Array[String]): Unit = {
    print("Enter the number: ")

    var numberString =""
    var a =0
    var b=0
    var c=0
    var rez: Double =0.0
    var z=0
    numberString = scala.io.StdIn.readLine()
    if ( (numberString.length() <= 10)) {
      println("Incorrect number");
      sys.exit(0)
    }else{
      numberString.substring(0,10)
    }

    for (i <- 1 to 10) {
      a = numberString.substring(0, 5).toInt

      b=  numberString.substring(5, 10).toInt
      c= a*b
      rez=c.toString().substring(0,3).toFloat / 1000
      z+=c

      if (z < 0) {
        z *= -1;
      }

      println(s"\na = ${a}  b = ${b}   c =  ${c}  rez =  ${rez} z = ${z}" );
      numberString= numberString.substring(1,numberString.length()-1)
      numberString="011" + z
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

  def inputNumber() : String = {

      var numberStr : String = "";

      print ("Enter the number: ")
      numberStr = scala.io.StdIn.readLine ()

      if ((numberStr.length () < 10) ) {
      println ("Incorrect number");
      sys.exit (0)
    } else {
      numberStr.substring (0, 10)
    }

      numberStr
  }


  def generateRandomNumber() = {

    val random = new Random();
    var generatedNumbers = Set[Int]()


    while (generatedNumbers.size < 15) {
      val randomNumber = random.nextInt(100)

      if (!generatedNumbers.contains(randomNumber)) {
        generatedNumbers += randomNumber
      }
    }

    println("Полученные числа:")
    println(generatedNumbers)

  }


  def main(args: Array[String]): Unit = {

    var a: Long = 0
    var b : Long = 0
    var c : Long = 0
    var rez: Float = 0
    var z : Long = 0

    var numberString: String = inputNumber();

    for (i <- 1 to 5) {
      a = substringFromSymbolsAtEvenPositions(numberString).toLong

      b = substringFromSymbolsAtOddPositions(numberString).toLong
      c = a * b

      rez = c.toString().substring(0, 3).toFloat / 1000

      z += c

      if(z < 0 ){
        z *= -1;
      }

      if(z.toString.length > 11) z = z.toString.substring(0,10).toLong;

      println(s"\na = ${a}  b = ${b}   c = ${c}  rez = ${rez} z = ${z}" );

      numberString = "011" + z
      numberString = numberString.substring(0, 11)

    }

//     generateRandomNumber();

  }
}
