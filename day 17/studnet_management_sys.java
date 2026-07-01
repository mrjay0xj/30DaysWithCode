import java.awt.event.KeyEvent;
import java.sql.PreparedStatement;
import java.sql.Statement;
import java.util.Random;
import java.util.Scanner;
import java.sql.DriverManager;
import java.sql.SQLException;

//Student management system

public class Main {
    static Scanner scanner = new Scanner(System.in);

    private static final String db_location = "jdbc:sqlite:mydb.db";

    public static void show_in_table() {
        String sql = "SELECT id,name,score FROM stdnt";

        try (var conn = DriverManager.getConnection(db_location);
            Statement stmt = conn.createStatement()) {
            stmt.execute(sql);
            System.out.println(stmt);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void add_to_table(int id, String name, double score) {
        String sql = "INSERT INTO stdnt (score,name,id) VALUES (?,?,?);";

        try (var conn = DriverManager.getConnection(db_location);
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(3, id);
            ps.setString(2, name);
            ps.setDouble(1, score);
            int rows = ps.executeUpdate();
            if (rows > 0) {
                System.out.println("insert success!");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void del_from_table(String name) {
        String sql = "DELETE FROM stdnt WHERE name IS ?;";

        try (var conn = DriverManager.getConnection(db_location);
            PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setString(1, name);
            int rows = ps.executeUpdate();
            if (rows > 0) {
                System.out.println("delete success!");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public static int generateID() {
        Random random = new Random();
        return random.nextInt(99999 - 11111 + 1) + 11111;
    }

    public static void main(String[] args) {
        while (true) {
            System.out.println("Commands:\n" +
                    "a -> adding student\n" +
                            "d -> delete student\n" +
                            "s -> show all studnets");
            System.out.print("Command: ");
            char cmd = scanner.next().toLowerCase().charAt(0);

            switch (cmd) {
                case 'a':
                    System.out.print("student name: ");
                    String std_name = scanner.next();
                    System.out.print("student score: ");
                    double std_score = scanner.nextDouble();
                    add_to_table(generateID(), std_name, std_score);
                    break;
                case 'd':
                    System.out.print("student name: ");
                    String d_std_name = scanner.next();
                    del_from_table(d_std_name);
                    break;
                case 's':
                    show_in_table();
                    break;
                default:
                    System.out.print("Unknown Command!");
                    break;
            }
        }
    }
}
