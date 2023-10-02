object Main8 {

  def countVowels(text: String): Int = {
    val vowels = "aeiouAEIOU"
    text.count(vowels.contains)
  }


  def findLowercaseWords(text: String): List[String] = {
    val words = text.split("\\W+").toList
    words.filter(_.nonEmpty).filter(_.head.isLower)
  }

  def main(args: Array[String]): Unit = {
    val text = "Hello agaiN to everybody Katty, Mikky"
    val lowercaseWords = findLowercaseWords(text)

    lowercaseWords.foreach(println)


    val vowelsCount = countVowels(text)

    println(s"Суммарное число всех гласных: $vowelsCount")

  }
}