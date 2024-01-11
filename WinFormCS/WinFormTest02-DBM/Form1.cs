using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Runtime.Remoting.Contexts;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormTest02_DBM
{
    public partial class frmDBManager : Form
    {
        public frmDBManager()
        {
            InitializeComponent();
        }
        //C:\\Users\\EMBEDDED\\source\\repos\\Intel\\WinFormCS\\WinFormTest02-DBM\\TestDB.mdf;
        string GetFileName(string sPath) //전체 경로 받음
        {
            string[] sa = sPath.Split('\\');
            return sa[sa.Length - 1];
        }
        SqlConnection sqlConn = new SqlConnection();
        SqlCommand sqlComm = new SqlCommand();
        string sConn = "Data Source=(LocalDB)\\MSSQLLocalDB;AttachDbFilename=C:\\Users\\EMBEDDED\\source\\repos\\Intel\\WinFormCS\\WinFormTest02-DBM\\TestDB.mdf;Integrated Security=True;Connect Timeout=30";
        
        private void mnuOpen_Click(object sender, EventArgs e)
        {
            //DB file select
            openFileDialog1.Filter = "MS-SQL Database file|*.mdf";
            if(DialogResult.OK == openFileDialog1.ShowDialog()) 
            {
                //@을 붙이면 \기호가 1개여도 경로를 인식한다. (매크로 기법)
                //보간문자열로 사용할려면 앞에 $를 붙여야 한다.
                string sConn = $"Data Source=(LocalDB)\\MSSQLLocalDB;AttachDbFilename={openFileDialog1.FileName};Integrated Security = True; Connect Timeout = 30";
                sqlConn.ConnectionString = sConn;
                sqlConn.Open();
                sqlComm.Connection = sqlConn; //여기까지가 데이터베이스 연결
                sbLabel1.BackColor = Color.LightSkyBlue;
                sbLabel1.Text = GetFileName(openFileDialog1.FileName);
            }
        }

        String[] RunSql(string sql) //Select vs Others
        {
            sqlComm.CommandText = sql; //sql을 이용하여 command 수행
            SqlDataReader sr = sqlComm.ExecuteReader(); //reader로 수행하게 됨
            if (sql.Trim().ToLower().Substring(0, 6) == "select")  //Trim은 공백문자, 엔터, 탭을 제거해줌 ToLower를 넣어 6글자면 select글자를 읽어올 수 있게 함
            {
                
                for (int i = 0; i < sr.FieldCount; i++)
                {
                    string colName = sr.GetName(i);
                    dataView.Columns.Add(colName, colName);
                }
            }
            for (int i = 0; i < sr.FieldCount; i++)
            {
                string colName = sr.GetName(i);
                dataView.Columns.Add(colName, colName);
            }
            for (;sr.Read();) //하나의 레코드를 한 줄씩 읽음 
            {
                int nRow = dataView.Rows.Add(); // 1 Line Add
                for (int i = 0; i < sr.FieldCount; i++)
                {
                    object o = sr.GetValue(i);
                    dataView.Rows[nRow].Cells[i].Value = o;
                }
            }
        }

        private void mnuSql1_Click(object sender, EventArgs e)
        {
            string sql = "Select * from person"; //sql문을 구성
        }
    }
}
