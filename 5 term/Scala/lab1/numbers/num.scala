object Numbers {
  def gcd(a: Int, b: Int): Int = {
    if (b == 0) a else gcd(b, a % b)
  }

  def sum(a: Int, b: Int): Unit = {
    var summa = a + b;

    println(s"$summa")
  }
}

object Main22 {
  def main(args: Array[String]): Unit = {
    print("Enter the first number: ")
    val a = scala.io.StdIn.readInt()
    print("Enter the second number: ")
    val b = scala.io.StdIn.readInt()

    val gcdValue = Numbers.gcd(a, b)
    println(s"The greatest common divisor of $a and $b is $gcdValue")

    Numbers.sum(a,b)

  }
}
