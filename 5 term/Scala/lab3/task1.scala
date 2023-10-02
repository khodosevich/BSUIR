object Main1 {
  def main(args: Array[String]): Unit = {
    val text = "Passport AB-123-436"
    val pattern = "3"

    val occurrences = pattern.r.findAllIn(text).length
    println(s"Число вхождений цифры 3: $occurrences")
  }
}