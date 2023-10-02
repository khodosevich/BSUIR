object Examples {
  def main(args: Array[String]): Unit = {
//    val str = "Hello, World!"
//    val newStr = str.replaceAll("o", "a")
//    println(newStr)
//
//    val str = "apple,banana,orange"
//    val arr = str.split(",")
//    println(arr.mkString(" ")) // "apple banana orange"

//    val str = "Hello, World!"
//    println(str.startsWith("Hello")) // true
//    println(str.endsWith("!")) // true

//    val str = "Hello, World!"
//    val subStr = str.substring(7, 12)
//    println(subStr) // "World"


//    val str = "Hello, World!"
//    val arr = str.toCharArray()
//    println(arr.mkString(" ")) // "H e l l o ,   W o r l d !"

//
//    val str = "Hello, World!"
//    println(str.toLowerCase) // "hello, world!"
//    println(str.toUpperCase) // "HELLO, WORLD!"


//    val str = "   Hello, World!   "
//    println(str.trim) // "Hello, World!"


//    val str = "Hello, World!"
//    println(str.indexOf("o")) // 4
//    println(str.lastIndexOf("o")) // 8

//    val str = "Hello, World!"
//    println(str.charAt(7)) // 'W'

//
//    val str =
//      """
//        |Hello,
//        |World!
//        |""".stripMargin
//    println(str) // "Hello,\nWorld!\n"


//    val str = "The quick brown fox jumps over the lazy dog"
//    val pattern = "fox".r
//    val matches = pattern.findAllIn(str)
//
//    matches.foreach(println)


    val regex = """(\d{3})-(\d{2})-(\d{4})""".r

    val str1 = "123-45-6789"
    val str2 = "abc-12-3456"

    val match1 = regex.findFirstMatchIn(str1)
    val match2 = regex.findFirstMatchIn(str2)

    match1 match {
      case Some(m) => println(s"Match found: ${m.group(0)}")
      case None => println("No match found")
    }

    match2 match {
      case Some(m) => println(s"Match found: ${m.group(0)}")
      case None => println("No match found")
    }


  }
}