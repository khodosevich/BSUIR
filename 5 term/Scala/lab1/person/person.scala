class Person {
  def hello(name :String ): Unit = println(s"hello, $name")
}

object Main22 {
  def main(args: Array[String]) : Unit = {
    val x = new Person();
    x.hello("matvey");
    x.hello("man");
  }
}
