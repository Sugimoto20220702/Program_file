using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace　リバーシ
{
    public partial class Form1 : Form
    {
        int blockS = 26;
        int[,] boardC = new int[8, 8];
        int[,] boardW = new int[8, 8];
        Bitmap boardImg;

        struct Result
        {
            public int numBl;
            public int numWh;
            public string plDayTime;
        }
        Result[] plResult = new Result[0];

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            pictureBox1.Width = pictureBox1.Height = blockS * 8 + 1;
            pictureBox1.BackColor = Color.ForestGreen;
            Board();
            TurnNumber(Color.White);
            checkBox1.Checked = checkBox2.Checked = false;
            button2.Enabled = button3.Enabled = false;
            groupBox1.Visible = false;
            resultIntput();
            radioButton2.Checked = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Array.Clear(boardC, 0, 64);
            Board();
            TurnNumber(Color.White);
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
                button2.Enabled = checkBox1.Checked;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            TurnNumber(label1.BackColor);
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            button3.Enabled = checkBox2.Checked;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if(DialogResult.Yes==MessageBox.Show("ちょっと　まって！！\n一手戻してm(_ _''m)","懇願",
                MessageBoxButtons.YesNo, MessageBoxIcon.Information))
            {
                Array.Copy(boardW, boardC, 64);
                pictureBox1.Image = boardImg;
                TurnNumber(label1.BackColor);
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            int[] NumSt = new int[2];
            NumSt = numberStone(boardC);
            MessageBox.Show("黒：" + NumSt[0] + "目　白：" + NumSt[1] + "目", "石目数", MessageBoxButtons.OK, MessageBoxIcon.Information);

        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            int bx, by, n;

            bx = e.X / blockS;
            by = e.Y / blockS;

            if (boardC[bx, by] != 0)
            {
                MessageBox.Show("この位置には既に石が打たれています。" + "\n重ねて、石を打つことはできません。",
                                                      "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            boardImg = new Bitmap(pictureBox1.Image);
            Array.Copy(boardC, boardW, 64);

            Stone(label1.BackColor, bx, by);
            n = StoneChange(label1.BackColor, bx, by);

            if (n == 0)
            {
                MessageBox.Show("この位置に石を打つことはできません。", "警告",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                Stone(Color.ForestGreen, bx, by);
                boardC[bx, by] = 0;
            }
            else
            {
                TurnNumber(label1.BackColor);
                if (skipCheck(label1.BackColor) == 0)
                {
                    TurnNumber(label1.BackColor);
                    string tmp;

                    if (skipCheck(label1.BackColor) == 0)
                    {
                        int[] nSt = new int[2];
                        nSt = numberStone(boardC);

                        if (nSt[0] > nSt[1])
                        {
                            tmp = "黒石の勝ちです！";
                            nSt[0] = 64 - nSt[1];
                        }
                        else if (nSt[1] > nSt[0])
                        {
                            tmp = "白石の勝ちです！";
                            nSt[1] = 64 - nSt[0];
                        }
                        else
                        {
                            tmp = "引き分けです！";
                            nSt[0] = nSt[1] = 32;
                        }
                        if (DialogResult.Yes == MessageBox.Show(tmp + "\n黒：" + nSt[0] + "目　白：" + nSt[1] +
                            "目\n" + "勝敗結果表に登録しますか？", "終局　勝敗", MessageBoxButtons.YesNo, MessageBoxIcon.Information))
                            resultEntry(nSt);
                    }
                    else
                    {
                        if (label1.BackColor == Color.White)
                            tmp = "黒は打つところがありません。\r\n 白手番 です。";
                        
                        else
                            tmp = "白は打つところがありません。\r\n 黒手番 です。";
               
                        MessageBox.Show(tmp, "通知", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            groupBox1.Visible = false;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (DialogResult.Yes == MessageBox.Show("対局勝敗結果を消去していいですか？", "確認", MessageBoxButtons.YesNo, MessageBoxIcon.Question))
            {
                label3.Text = "";
                Array.Resize(ref plResult, 0);
                System.IO.File.Delete("..\\resultOut.txt");
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            resultShow();
        }

        public void resultEntry(int[] nSt)
        {
            int recNo = plResult.Length;
            Array.Resize(ref plResult,plResult.Length+1);

            plResult[recNo].numBl = nSt[0];
            plResult[recNo].numWh = nSt[1];
            plResult[recNo].plDayTime =DateTime.Now.ToString("yyyy/MM/dd HH:mm");

            resultShow();
        }

        public void resultShow()
        {
            int i, n = resultSort();

            label3.Text = "";
            if (n > 10) n = 10;
            for (i = 0; i < n; i++)
                label3.Text += string.Format("{0, 2}:{1} {2, 2}:{3, 2}\n",
                    i + 1, plResult[i].plDayTime, plResult[i].numBl, plResult[i].numWh);
            groupBox1.Visible = true;
            resultOutput();
        }

        public int resultSort()
        {
            int i, n = plResult.Length;

            if (radioButton3.Checked == true)
            {
                int[] work = new int[n];
                for (i = 0; i < n; i++) work[i] = -Math.Abs(plResult[i].numBl - plResult[i].numWh);
                Array.Sort(work, plResult);
            }
            else
            {
                string[] work = new string[n];
                for (i = 0; i < n; i++) work[i] = plResult[i].plDayTime;
                Array.Sort(work, plResult);
                if (radioButton2.Checked == true) Array.Reverse(plResult);
            }

            return n;
        }

        public void resultIntput()
        {
            if (System.IO.File.Exists("..\\resultOut.txt") == true)
            {
                string[] num = new string[3];

                System.IO.StreamReader fs;
                fs = new System.IO.StreamReader("..\\resultOut.txt");

                int recNo = 0;
                while (fs.EndOfStream == false)
                {
                    Array.Resize(ref plResult, recNo + 1);
                    num = fs.ReadLine().Split(',');
                    plResult[recNo].numBl = int.Parse(num[0]);
                    plResult[recNo].numWh = int.Parse(num[1]);
                    plResult[recNo].plDayTime = num[2];
                    recNo++;
                }
                fs.Close();
            }
        }

        public void resultOutput()
        {
            int i, recNo = plResult.Length;

            System.IO.StreamWriter fs;
            fs = new System.IO.StreamWriter("..\\resultOut.txt");

            for (i = 0; i < recNo; i++) fs.WriteLine(string.Format("{0},{1},{2}", 
                         plResult[i].numBl, plResult[i].numWh, plResult[i].plDayTime));

            fs.Close();
        }

        public int skipCheck(Color Scol)
        {
            int i, j, n, sc = (Scol == Color.Black ? 1 : -1);
            int[,] boardT = new int[8, 8];
            Bitmap boardImgT = new Bitmap(pictureBox1.Image);
            Array.Copy(boardC, boardT, 64);

            n = 0;
            for (i = 0; i < 8; i++)
                for (j = 0; j < 8; j++)
                {
                    if (boardC[i,j] == 0)
                    {
                        boardC[i, j] = sc;
                        n = StoneChange(Scol, i, j);
                        if (n != 0)
                        {
                             Array.Copy(boardT, boardC, 64);
                            pictureBox1.Image = boardImgT;
                            return n;
                        }
                        boardC[i, j] = 0;
                    }
                }

            return 0;
        }

        public int[] numberStone(int[,] boardC)
        {
            int[] nSt = new int[2] { 0, 0 };
            int i, j;
            for (i=0; i < 8;i++)
                for (j = 0; j < 8; j++)
                    if (boardC[i, j] == 1) nSt[0]++;
                    else if (boardC[i, j] == -1) nSt[1]++;
            return nSt;
        }

        public void TurnNumber(Color col)
        {
            if (label1.BackColor == Color.Black)
            {
                label1.BackColor = Color.White;
                label1.ForeColor = Color.Black;
                label1.Text = "白手番";
            }
            else
            {
                label1.BackColor = Color.Black;
                label1.ForeColor = Color.White;
                label1.Text = "黒手番";
            }
        }

        public void Board()
        {
            pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            Graphics gh = Graphics.FromImage(pictureBox1.Image);
            gh.Clear(pictureBox1.BackColor);

            int i, w = pictureBox1.Width;

            for (i = 0; i < w; i += blockS)
            {
                gh.DrawLine(Pens.Black, i, 0, i, w);
                gh.DrawLine(Pens.Black, 0, i, w, i);
            }
            
            gh.Dispose();
            pictureBox1.Refresh();

            Stone(Color.White, 3, 3);
            Stone(Color.Black, 3, 4);
            Stone(Color.White, 4, 4);
            Stone(Color.Black, 4, 3);
        }

        public void Stone(Color SCol, int x, int y)
        {
            Graphics gh = Graphics.FromImage(pictureBox1.Image);
           
            gh.FillEllipse(new SolidBrush(SCol), x * blockS + 1, y * blockS + 1, blockS - 2, blockS - 2);
            gh.Dispose();

            pictureBox1.Refresh();
            boardC[x, y] = (SCol == Color.Black ? 1 : -1);
        }

        public int StoneChange(Color SCol, int x, int y)
        {
            int c, cc, xx, yy, i, j, n = 0;
            cc = (Color.Black == SCol ? 1 : -1);
            c = -1 * cc;

            xx = x;  //左
            while(xx>0)
            {
                xx--;
                if (boardC[xx, y] != c) break;
            }
            if (boardC[xx, y] == cc)
                for (i = x - 1; i > xx; i--, n++)
                    Stone(SCol, i, y);
            xx = x;           //左下
            yy = y;
            while (xx > 0 && yy < 7) 
            {
                xx--;
                yy++;
                if (boardC[xx, yy] != c) break;
            }
            if (boardC[xx, yy] == cc)
                for (i = x - 1,j=y+1; i > xx; i--,j++, n++)
                    Stone(SCol, i, j);
            xx = x;　　　　　　　　　//左上
            yy = y;
            while (xx > 0 && yy > 0)
            {
                xx--;
                yy--;
                if (boardC[xx, yy] != c) break;
            }
            if (boardC[xx, yy] == cc)
                for (i = x - 1, j = y - 1; i > xx; i--, j--, n++)
                    Stone(SCol, i, j);
            xx = x;          //上
            yy = y;
            while (yy > 0)
            {
                yy--;
                if (boardC[xx, yy] != c) break;
            }
            if (boardC[xx, yy] == cc)
                for (j = y - 1; j > yy; j--, n++)
                    Stone(SCol, x, j);
            xx = x;        //下
            yy = y;
            while (yy < 7)
            {
                yy++;
                if (boardC[xx, yy] != c) break;
            }
            if (boardC[xx, yy] == cc)
                for (j = y + 1; j < yy; j++, n++)
                    Stone(SCol, x, j);
            xx = x;          //右
            yy = y;
            while (xx < 7)
            {
                xx++;
                if (boardC[xx, yy] != c) break;
            }
            if (boardC[xx, yy] == cc)
                for (i = x + 1; i < xx; i++, n++)
                    Stone(SCol, i, y);
            xx = x;     //右下
            yy = y;
            while (xx < 7 && yy < 7)
            {
                xx++;
                yy++;
                if (boardC[xx, yy] != c) break;
            }
            if (boardC[xx, yy] == cc)
                for (i = x + 1, j = y + 1; i < xx; i++, j++, n++)
                    Stone(SCol, i, j);
            xx = x;                  //右上
            yy = y;
            while (xx < 7 && yy > 0)
            {
                xx++;
                yy--;
                if (boardC[xx, yy] != c) break;
            }
            if (boardC[xx, yy] == cc)
                for (i = x + 1, j = y - 1; i < xx; i++, j--, n++)
                    Stone(SCol, i, j);
            return n;
        }

    }
}
