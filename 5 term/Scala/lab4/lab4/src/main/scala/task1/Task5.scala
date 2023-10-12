package task1

import org.apache.spark.sql.{Encoders, SparkSession}

object Task5 extends App{

  var encoder = Encoders.kryo[String]
  val spark = SparkSession.builder().master("local[*]").appName("lab4").getOrCreate()

  val data = spark.read.textFile("src/main/scala/task1/text")


  val wordsRDD = data.flatMap(l => l.split("\\s"))(encoder)

  val filterData = wordsRDD.filter(word => word.contains("ee"))

  if (!filterData.isEmpty) {
    filterData.foreach(el => println(el))
  }


}
