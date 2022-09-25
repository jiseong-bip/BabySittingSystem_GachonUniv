<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="mydb.MainCon" %>
<%@ page import="mydb.DBUtil" %>
<%@ page import="java.sql.*" %>

<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<%MainCon mc = new MainCon();%>
<body>
<span><%=mc.getTemp() %></span>
</body>
</html> 