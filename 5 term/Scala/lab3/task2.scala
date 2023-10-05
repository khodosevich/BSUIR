object Main2 {


  def main(args: Array[String]): Unit = {
    val text = "Passport AB-123-436"
    val digits = text.replaceAll("\\D", "")
    var sum = 0

    for (char <- digits) {
      sum += char.asDigit
    }

    println(s"Сумма всех цифр: $sum")
  }

}