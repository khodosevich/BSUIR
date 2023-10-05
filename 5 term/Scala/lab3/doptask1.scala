object Test1 {

  def findDoubledVowels(text: String): List[String] = {
    val regex = """([aeiouAEIOU])\1""".r
    regex.findAllIn(text).toList
  }


  def main(args: Array[String]): Unit = {

    val text = "matvey hee yy hello oo"
    val doubledConsonants = findDoubledVowels(text)

    println(s"Удвоенные согласные: $doubledConsonants")

  }
}