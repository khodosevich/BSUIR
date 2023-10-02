object Main2 {
  def main(args: Array[String]): Unit = {
    val text = "Passport AB-123-436"
    val digits = text.replaceAll("\\D", "").map(_.asDigit)
    val sum = digits.sum
    println(s"Сумма всех цифр: $sum")

  }
}