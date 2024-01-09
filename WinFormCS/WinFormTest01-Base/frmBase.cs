using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormTest01_Base
{
    public partial class frmBase : Form
    {
        int EncMode = 0; // 0 : UTF-8, 1 : ANSI
        public frmBase()
        {
            InitializeComponent();
            if(EncMode == 0 )
                mnuUtf8_Click(null, null);  // UTF8 call
            else mnuAnsi_Click(null, null); // ANSI call
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            mnuOpen_Click(sender, e);
        }
        string ReadBuf;
        Encoding enc = Encoding.UTF8;
        private void mnuOpen_Click(object sender, EventArgs e)
        {
            DialogResult ret = openFileDialog1.ShowDialog();
            if (ret == DialogResult.OK)
            {
                string fn = openFileDialog1.FileName;
                
                FileStream fs = new FileStream(fn, FileMode.Open); //FileStream(파일 이름, 여는 방법)
                StreamReader sr = new StreamReader(fs, enc);
                tbMemo.Text += sr.ReadToEnd();
                sr.Close();
                fs.Close();

                //while(true) // C#에서 무한루프 사용할 땐 null, 1, 0 값 안돼 bool값을 넣어야 한다
                //{
                //    string str = sr.ReadLine(); //한줄 씩 읽는 방법
                //    if (str == null) break;
                //    tbMemo.Text += str;
                //}

            }
        }

        private void mnuSave_Click(object sender, EventArgs e)
        {
            DialogResult ret = saveFileDialog1.ShowDialog();
            if (ret == DialogResult.OK)
            {
                string fn = saveFileDialog1.FileName;

                FileStream fs = new FileStream(fn, FileMode.Create); //FileStream(파일 이름, 여는 방법) 저장하니까 무조건 Create
                StreamWriter sw = new StreamWriter(fs, enc);
                sw.Write(tbMemo.Text);
                sw.Close();
                fs.Close();
            }
        }

        private void mnuAnsi_Click(object sender, EventArgs e)
        {
            sbLabel1.Text = "ANSI"; //Ansi탭을 눌렀을 때 라벨의 텍스트를 바꿔줌
            mnuAnsi.Checked = true;
            mnuUtf8.Checked = false;
            enc = Encoding.Default;
            byte[] ba = Encoding.Default.GetBytes(tbMemo.Text); //default = Ansi
            byte[] bb = Encoding.Convert(Encoding.UTF8, Encoding.Default, ba);
            tbMemo.Text = Encoding.Default.GetString(bb);
        }

        private void mnuUtf8_Click(object sender, EventArgs e)
        {
            sbLabel1.Text = "UTF-8";
            mnuAnsi.Checked = false;
            mnuUtf8.Checked = true;
            enc = Encoding.UTF8;
        }

        private void mnuAbout_Click(object sender, EventArgs e)
        {
            string s;
            frmAbout frm = new frmAbout();
            DialogResult = frm.ShowDialog();
            if(DialogResult == DialogResult.OK) s = "About... OK";
            else                                s = "About... Cancel";
            sbLabel2.Text = s;
        }
    }
}
