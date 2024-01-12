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

namespace WinFormTest03_Paint
{
    public partial class frmPaint : Form
    {
        Graphics g = null;
        Pen pen = null;
        Brush brush = null;
        Bitmap bmCanvas = null;

        int dMode = 0;  // 0 : Not, 1 : Pen, 2 : Line, 3 : Rect, 4 : Circle, 5 : Text
        int dFlag = 0;  // 0 : Open, 1 : Pressed 마우스 버튼
        Point p1, p2, p3;
        Point cp1, cp2, cp3;    // Screen 좌표계
        public frmPaint()
        {
            InitializeComponent();
            frmPaint_ResizeEnd(null, null);
            pen = new Pen(Color.FromArgb(204, 204, 255), 5); // 색상, 선 두께
            sbLabel4.Text = "";
        }

        private void frmPaint_ResizeEnd(object sender, EventArgs e)
        {   //canvas box size
            int draw_X = Canvas.Width, draw_Y = Canvas.Height;
            if(bmCanvas == null)
            {
                bmCanvas = new Bitmap(draw_X, draw_Y);
                Canvas.Image = bmCanvas;
            }
            else
            {
                Bitmap tBmp = new Bitmap(draw_X, draw_Y); // No Image
                Graphics tg = Graphics.FromImage(tBmp);
                tg.DrawImage(bmCanvas, 0, 0); // 백업
                bmCanvas.Dispose(); // 기존 이미지 해제
                bmCanvas = tBmp;
                Canvas.Image = bmCanvas;
            }
            g = Graphics.FromImage(bmCanvas);

        }
        private void frmPaint_Resize(object sender, EventArgs e)
        {
            if (WindowState == FormWindowState.Maximized) frmPaint_ResizeEnd(sender, e);

        }

        private void Canvas_MouseDown(object sender, MouseEventArgs e)
        {
            dFlag = 1; 
            p1 = e.Location; p2 = e.Location; p3 = e.Location;
            cp1 = cp2 = cp3 = ((Control)sender).PointToScreen(p1);
        }

        private void Canvas_MouseUp(object sender, MouseEventArgs e)
        {
            switch(dMode)
            {
                case 2: //Line draw
                    g.DrawLine(pen, p1, e.Location);
                    Canvas.Invalidate();
                    break;
                default: break;
            }
            dFlag = 0;
        }

        private void Canvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.X < 0 || e.Y < 0 || e.X > Canvas.Width || e.Y > Canvas.Height) return;
            if (dFlag != 0) switch(dMode)
            {
                case 1: // 연필
                    g.DrawLine(pen, p1, e.Location);
                    p1 = e.Location;
                    break;
                case 2: // 선
                    cp3 = ((Control)sender).PointToScreen(e.Location);
                    ControlPaint.DrawReversibleLine(cp1, cp2, DefaultBackColor); //ControlPaint는 시스템 속성
                    ControlPaint.DrawReversibleLine(cp1, cp3, DefaultBackColor);
                    cp2 = cp3;
                    //g.DrawLine(pen, p1, e.Location);
                    break;
                case 3: // 사각형
                case 4: // 원
                default: break;
            }
            Canvas.Invalidate();
            string str = $"{e.X} x {e.Y}";  // e.은 마우스와 관련된 정보
            sbLabel1.Text = str;
        }

        private void mnuDraw_Click(object sender, EventArgs e)
        {
            dMode = 1; // 연필
            sbLabel4.Text = "연필";
        }

        private void mnuLine_Click(object sender, EventArgs e)
        {
            dMode = 2; // 선
            sbLabel4.Text = "선";
        }

        private void mnuRect_Click(object sender, EventArgs e)
        {
            dMode = 3; // 사각형
            sbLabel4.Text = "사각형";
        }

        private void mnuTestSine_Click(object sender, EventArgs e)
        {
            mnuErase_Click(sender, e);
            List<double> data = new List<double>();
            for(int i = 0; i < 360; i++)  //X, Y
            {
                data.Add(Math.Sin(3.141592 / 180 * i));
            }
            int l = 0, t = 0, r = Canvas.Width, b = Canvas.Height;
            int range = r - l - 40;
            int step = range / 360;
            int amp = -(b - 20) / 2;
            int xoffset = 20;
            int yoffset = b / 2;
            g.DrawLine(pen, new Point(l + 20, b / 2), new Point(r - 20, b / 2));
            g.DrawLine(pen, new Point(l + 20, 10), new Point(l + 20, b - 10));
            PointF p1, p2; // 값이 double
            p1 = new PointF(xoffset, yoffset); //최초 스타트 위치
            for (int i = 0; i < 360; i++)  //X, Y
            {
                p2 = new PointF(i * step + xoffset, (float)data[i] * amp + yoffset);
                g.DrawLine(pen, p1, p2);
                p1 = p2;
            }
            Canvas.Invalidate();
        }

        private void mnuOpen_Click(object sender, EventArgs e)
        {
            DialogResult ret = openFileDialog1.ShowDialog();

            if (ret == DialogResult.OK)
            {
                string fn = openFileDialog1.FileName;

                try
                {
                    // 이미지 파일을 PictureBox에 로드
                    Canvas.Image = Image.FromFile(fn);
                }
                catch (Exception ex)
                {
                    MessageBox.Show("파일을 열 수 없습니다. 오류 메시지: " + ex.Message);
                }
            }
        }

        private void mnuCircle_Click(object sender, EventArgs e)
        {
            dMode = 4; // 원
            sbLabel4.Text = "원";
        }

        private void mnuText_Click(object sender, EventArgs e)
        {
            dMode = 5; // 문자 쓰기
            sbLabel4.Text = "문자";
        }

        private void mnuErase_Click(object sender, EventArgs e)
        {
            g.Clear(Color.FromArgb(245, 243, 255));
        }

        private void Canvas_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            Pen pen = new Pen(Color.FromArgb(204, 204, 255));
            Point p1 = new Point(Left, Top);
            Point p2 = new Point(Right, Bottom);
            Point p3 = new Point(Left, Bottom);
            Point p4 = new Point(Right, Top);
            g.DrawLine(pen, p1, p2);
            g.DrawLine(pen, p3, p4);
        }
    }
}
