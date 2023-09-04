package Demo


class MyInt( val value: Int)  extends AnyVal {
  override def toString: String = s"MyInt ($value)"

  def +(other: MyInt) = new MyInt(value + other.value)
  def -(other: MyInt) = new MyInt(value - other.value)
  def *(other: MyInt) = new MyInt(value * other.value)
  def /(other: MyInt) = new MyInt(value / other.value)
  def ::(other: MyInt) = new MyInt(s"${other.value}$value".toInt)
}

object Main {
  def main(args: Array[String]): Unit = {
    val a = new MyInt(5)
    val b = new MyInt(7)
    println(a.toString)

    println(a.+(b))
    println(a.-(b))
    println(a.*(b))
    println(a./(b))

    println( a + b * b )

    println(b :: a :: a :: a)

    val list = Nil.::(3).::(4).::(4)

    println( 9 +: list :+ 8)

  }
}