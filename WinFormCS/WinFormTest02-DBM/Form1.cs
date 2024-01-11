using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Diagnostics.Eventing.Reader;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Linq.Expressions;
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

        ArrayList ColName = new ArrayList();    // 필드 이름 List
        List<object[]> RunSql(string sql) //Select vs Others
        {
            List<object[]> result = new List<object[]>(); //result 객체 선언
            sqlComm.CommandText = sql; //sql을 이용하여 command 수행
            try
            {
                if (sql.Trim().ToLower().Substring(0, 6) == "select")  //Trim은 공백문자, 엔터, 탭을 제거해줌 ToLower를 넣어 6글자면 select글자를 읽어올 수 있게 함
                {
                    SqlDataReader sr = sqlComm.ExecuteReader(); //reader로 수행하게 됨
                    ColName.Clear();
                    for (int i = 0; i < sr.FieldCount; i++) // Column Name
                    {
                        ColName.Add(sr.GetName(i));
                    }
                    for (; sr.Read();)
                    {
                        object[] oarr = new object[sr.FieldCount];
                        sr.GetValues(oarr);
                        result.Add(oarr);
                        //string str = "";
                        //for (int i = 0; i < sr.fieldcount; i++)
                        //{
                        //    object o = sr.getvalue(i);
                        //    if (i == 0) str = $"{o}";
                        //    else        str += $",{o}";
                        //}
                    }
                    sr.Close();
                }
                else
                {
                    int n = sqlComm.ExecuteNonQuery();
                }
                sbLabel3.Text = "OK";
                return result;
            }
            catch (Exception ex)
            {
                sbLabel3.AutoSize = true;
                sbLabel3.BackColor = Color.FromArgb(255, 167, 167);
                sbLabel3.Text = ex.Message;
                return null;
            }
        }

        private void mnuRun_Click(object sender, EventArgs e)
        {
            string sql = tbSql.SelectedText;
            if (sql == "") sql = tbSql.Text;
            List<object[]> r = RunSql(sql);
            if (r == null) return;
            dataView.Rows.Clear();
            dataView.Columns.Clear();
            for(int i = 0; i < ColName.Count; i++)
            {
                string colName = (string)ColName[i];
                dataView.Columns.Add(colName, colName);
            }
            for (int i = 0; i < r.Count; i++)
            {
                int nRow = dataView.Rows.Add(); // 1 Line Add
                object[] o = r[i];
                for (int j = 0; j < ColName.Count; j++)
                {
                    dataView.Rows[nRow].Cells[j].Value = o[j];
                }
            }
        }

        private void mnuFont_Click(object sender, EventArgs e)
        {
            if (fontDialog1.ShowDialog() == DialogResult.OK)
            {
                tbSql.Font = fontDialog1.Font;
                sbLabel2.Text = tbSql.Font.Name;
            }
        }

        private void mnuSave_Click(object sender, EventArgs e)
        {
            DialogResult ret = saveFileDialog1.ShowDialog();
            if (ret == DialogResult.OK)
            {
                string fn = saveFileDialog1.FileName;
                FileStream fs = new FileStream(fn, FileMode.Create);
                StreamWriter sw = new StreamWriter(fs);
                sw.Write(tbSql.Text);
                sw.Close();
                fs.Close();
            }

        }
    }
}
