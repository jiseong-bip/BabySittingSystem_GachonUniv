<%@ page language="java" contentType="application/json; charset=UTF-8"
pageEncoding="UTF-8"%>
<%@ page import="mydb.MainCon" %>
<%@ page import="mydb.DBUtil" %>
<%@ page import="java.sql.*" %>
<%@ page import="org.json.simple.JSONArray"%>

<%
MainCon mc = new MainCon();
String name = (String)session.getAttribute("name");
JSONArray jsonArray = mc.getJSONArray(name);

//out.println(jsonArray);
%>

<%=jsonArray %>

