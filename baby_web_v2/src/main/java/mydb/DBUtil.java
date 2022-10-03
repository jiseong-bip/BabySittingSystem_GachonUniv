package mydb;
import java.sql.*;

public class DBUtil {
		final static String DRIVER = "com.mysql.jdbc.Driver";
		final static String URL = "jdbc:mysql://192.168.0.152:3306/status?serverTimezone=UTC";
		//final static String URL = "jdbc:mysql://221.142.47.16:5900/status?serverTimezone=UTC";
		final static String USER = "root";
		final static String PW = "1q2w3e4r!";
		
		static{
		//1. JDBC 드라이버 로드 
			try{
				Class.forName(DRIVER);
			}catch(ClassNotFoundException e){
				System.out.println("JDBC NOT FOUND");
			}
		
		}
		
		// 데이터베이스 서버 연결 
		public static Connection getConnection() {
			//System.out.println("---- MySQL JDBC 연결-------");
			//System.out.println("---- MySQL JDBC 연결-------");
			Connection con = null;
			try {
				con=DriverManager.getConnection(URL,USER,PW);
				//System.out.println("Connection ok");
				
			}catch(SQLException e) {
				System.out.println("SQL 연결 실패 error");
			}
			return con;
			
		}
		// DB 종료 - 자원반납 
		
		/* insert, update, delete -> excuteupdate를 하기위한 메소드 */
		public static void close(PreparedStatement pstmt, Connection con){
			if(pstmt !=null){
				// 실행될때와 반대로 거꾸로 작성
				try{
					pstmt.close();
				}catch(SQLException sqle){
					System.out.println("SQLException e");
				}
			}if(con !=null){
				try{ 
					con.close();
				}catch(SQLException sqle){
					System.out.println("SQLException e");
				}
			}
			
		}
		/* select 용 excuteQuery */
		public static void close(ResultSet rs, PreparedStatement pstmt, Connection con){
			if(rs != null){
				try{
					rs.close();
					//System.out.println("close");
				}catch(SQLException sqle){
					System.out.println("SQLException");
				}
			}if(pstmt !=null){
				try{
					pstmt.close();
				}catch(SQLException sqle){
					System.out.println("SQLException");
				}
			}if(con !=null){
				try{
					con.close();
				}catch(SQLException sqle){
					System.out.println("SQLException");
				}
				
			
			}
		}


}

