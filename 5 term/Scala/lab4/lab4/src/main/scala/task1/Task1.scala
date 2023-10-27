package task1

import org.apache.spark.sql.{Encoders, SparkSession}

object Task1 extends App {

  val spark = SparkSession.builder().master("local[*]").appName("lab4").getOrCreate()
  var encoder = Encoders.kryo[String]


  val data = spark.read.textFile("src/main/scala/task1/text")

  val stopWord = Set("world","In","the","From")

  val wordsRDD = data.flatMap(l => l.split("\\s"))(encoder)

  val filterData = wordsRDD.filter(word => !stopWord.contains(word))

  filterData.foreach(el => println(el))

}
