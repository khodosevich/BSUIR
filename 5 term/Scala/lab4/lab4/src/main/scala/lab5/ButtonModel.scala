package lab5



import java.awt.Color
import java.awt.event.ActionEvent
import java.awt.event.ActionListener
import java.sql.DriverManager
import javax.swing.{JButton, JFrame, JLabel, JTextField, SwingUtilities}

//group by макс прибыль через
//запрос все товары стоимость от 10 до 40 between

object ButtonModule {
  val frame = new JFrame("My Application")
  frame.setSize(800, 600)
  frame.setLayout(null)
  frame.setBackground(Color.BLUE)

  def main(args: Array[String]): Unit = {
    SwingUtilities.invokeLater(() => {

      val label1 = new JLabel("Product")
      val label2 = new JLabel("Price")
      val label3 = new JLabel("Count")
      val label4 = new JLabel("Debug")

      label1.setBounds(220, 220, 70, 20)
      label2.setBounds(360, 220, 70, 20)
      label3.setBounds(500, 220, 70, 20)
      label4.setBounds(360, 50, 120, 20)

      val button1 = new JButton("Insert")
      val button2 = new JButton("Select")
      val button3 = new JButton("Max price")
      val button4 = new JButton("Count > 40")
      val button5 = new JButton("10 and 40")

      val textField = new JTextField(20)
      val textField2 = new JTextField(20)
      val textField3 = new JTextField(20)
      val textField4 = new JTextField(20)

      button1.setBounds(220, 160, 120, 20)
      button2.setBounds(360, 160, 120, 20)
      button3.setBounds(500, 160, 330, 20)
      button4.setBounds(360, 120, 320, 20)
      button5.setBounds(30, 30, 100, 50)

      textField.setBounds(220, 250, 120, 80)
      textField2.setBounds(360, 250, 120, 80)
      textField3.setBounds(500, 250, 120, 80)
      textField4.setBounds(360, 80, 120, 20)

      button2.setBackground(Color.RED)
      button3.setBackground(Color.BLUE)
      button5.setBackground(Color.BLUE)


      frame.add(button5)
      frame.add(label4)
      frame.add(textField4)
      frame.add(button4)
      frame.add(button1)
      frame.add(button2)
      frame.add(button3)
      frame.add(label1)
      frame.add(textField)
      frame.add(label2)
      frame.add(textField2)
      frame.add(label3)
      frame.add(textField3)


      button1.addActionListener(new ActionListener {
        override def actionPerformed(e: ActionEvent): Unit = {
          val url = "jdbc:mysql://localhost:3306/lab_5"
          val username = "root"
          val password = "15820311"
          Class.forName("com.mysql.jdbc.Driver")
           Class.forName("org.gjt.mm.mysql.Driver")

          val conn = DriverManager.getConnection(url, username, password)

          try {
            val stmt = conn.createStatement()
            val rs = stmt.execute("INSERT INTO stock(product,price,count_of_products) VALUES ('" + textField.getText + "'," + textField2.getText + "," + textField3.getText + ")")

            textField.setText("")
            textField2.setText("")
            textField3.setText("")

            textField4.setText("Added new row")

          }
          finally {
            conn.close()
          }
        }
      })


      button2.addActionListener(new ActionListener {
        override def actionPerformed(e: ActionEvent): Unit = {

          {
            val url = "jdbc:mysql://localhost:3306/lab_5"
            val username = "root"
            val password = "15820311"

            Class.forName("com.mysql.jdbc.Driver")
            val conn = DriverManager.getConnection(url, username, password)

            try {
              val stmt = conn.createStatement()
              val prod_name = textField.getText().trim()
              val rs = stmt.executeQuery("SELECT * FROM stock WHERE product ='" + prod_name + "'")
              while (rs.next()) {

                val name = rs.getString("product")
                val price = rs.getInt("price")
                val count = rs.getString("count_of_products")
                // println(s"name=$name, price=$price")
                textField2.setText("" + price)
                textField3.setText("" + count)
                textField.setText(name)
              }
            } finally {
              conn.close()
            }
          }
        }
      })


      button3.addActionListener(new ActionListener {
        override def actionPerformed(e: ActionEvent): Unit = {
          val url = "jdbc:mysql://localhost:3306/lab_5"
          val username = "root"
          val password = "15820311"

          Class.forName("com.mysql.jdbc.Driver")
          val conn = DriverManager.getConnection(url, username, password)

          try {
            val stmt = conn.createStatement()


            val rs = stmt.executeQuery("SELECT product, price, count_of_products, MAX(price) AS max_profit\nFROM stock\nGROUP BY product, price, count_of_products\nHAVING price = MAX(price)\nOrder by max_profit Desc limit 1")

            rs.next()

            val name = rs.getString("product")
            val price = rs.getInt("price")
            val count = rs.getInt("count_of_products")

            textField.setText(name)
            textField2.setText(price.toString)
            textField3.setText(count.toString)

          } finally {
            conn.close()
          }
        }
      })

      button4.addActionListener(new ActionListener {
        override def actionPerformed(e: ActionEvent): Unit = {
          val url = "jdbc:mysql://localhost:3306/lab_5"
          val username = "root"
          val password = "15820311"

          var nameBuilder = new StringBuilder("")
          var priceBuilder = new StringBuilder("")
          var countBuilder = new StringBuilder("")

          Class.forName("com.mysql.jdbc.Driver")
          val conn = DriverManager.getConnection(url, username, password)

          try {
            val stmt = conn.createStatement()


            val rs = stmt.executeQuery("SELECT * FROM stock WHERE count_of_products > 40")

            while(rs.next()){
              val name = rs.getString("product")
              val price = rs.getInt("price")
              val count = rs.getInt("count_of_products")

              nameBuilder.append(name).append("\n")
              priceBuilder.append(price).append("\n")
              countBuilder.append(count).append("\n")


              println("product: " + name + ", price: " + price + ", count: " + count)

              textField.setText(nameBuilder.toString())
              textField2.setText(priceBuilder.toString())
              textField3.setText(countBuilder.toString())

            }



          } finally {
            conn.close()
          }
        }
      })

      button5.addActionListener(new ActionListener {
        override def actionPerformed(e: ActionEvent): Unit = {
          val url = "jdbc:mysql://localhost:3306/lab_5"
          val username = "root"
          val password = "15820311"

          var nameBuilder = new StringBuilder("")
          var priceBuilder = new StringBuilder("")
          var countBuilder = new StringBuilder("")

          Class.forName("com.mysql.jdbc.Driver")
          val conn = DriverManager.getConnection(url, username, password)

          try {
            val stmt = conn.createStatement()


            val rs = stmt.executeQuery("SELECT * FROM stock WHERE price between 10 and 40")

            while (rs.next()) {
              val name = rs.getString("product")
              val price = rs.getInt("price")
              val count = rs.getInt("count_of_products")

              nameBuilder.append(name).append("\n")
              priceBuilder.append(price).append("\n")
              countBuilder.append(count).append("\n")


              println("product: " + name + ", price: " + price + ", count: " + count)

              textField.setText(nameBuilder.toString())
              textField2.setText(priceBuilder.toString())
              textField3.setText(countBuilder.toString())

            }


          } finally {
            conn.close()
          }
        }
      })

      frame.setLocationRelativeTo(null)
      frame.setVisible(true)

    })

  }
}
