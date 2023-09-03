package Demo

import scala.io.StdIn
object ValuesAndTypes {

  val a : Int = 5;
  val b = 65;

  val Boolean : Boolean = true;

  val aChar: Char = 'a';

  val aString : String = "hello";

  val aShort : Short = 4444;
  val aLong : Long = 44444444L;

  val aFlaot : Float = 4.3f;

  val db : Double = 4.34;

  def max(a : Int , b : Int ) : Unit = {
    println(if(a > b ) a else b);
  }


  def main(args: Array[String]): Unit = {

//    print( aChar , aString, aShort , Boolean , db );

    val name = StdIn.readLine("hello , enter your name: ");

    println(s"\nhey , $name !")

    print("first : " );
    val first = StdIn.readInt();
    print("second : " );
    val second = StdIn.readInt();

    this.max(first,second);

    println("db is " +  db.getClass)

    //any все типы наследуются от any
    println(1.isInstanceOf[Any])

    val aa : Char = 'a';
    val toDb : Double = aa;
//    val toLn : Long = toDb; error
    println(toDb)


  }
}
