object Main3 {
  def main(args: Array[String]): Unit = {
    val text = "123+723=846"
    val operations = text.filter(c => c == '+' || c == '-' || c == '*' || c == '/' || c == '=' )
    println(s"Символы арифметических операций: $operations")

  }
}