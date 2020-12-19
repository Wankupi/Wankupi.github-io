
let $ = (s => document.querySelectorAll(s));
let top_panel = $("#top-panel")[0], block = $("#articles")[0], artCount = $("#art-count")[0];
let count = {}, arts;

let search = new URLSearchParams(location.search).getAll("q");

if (search.length > 0) $("header>.title")[0].innerText = "搜索结果";

function checkArt(a) {
  if (search.length == 0) return true;
  for (let i = 0; i < search.length; ++i)
    if (a.title.match(search[i]) != null || a.type.match(search[i]) != null ||
      a.outline.match(search[i]) != null || a.path.match(search[i]) != null)
      return true;
  return false;
}

function putArts() {
  function DateToHTML(d) {
    if (d) {
      let t = new Date(d);
      return `${t.getFullYear()}-${(t.getMonth() + 1).toString().padStart(2, '0')}-${t.getDate().toString().padStart(2, '0')} ` +
        `${t.getHours().toString().padStart(2, "0")}:${t.getMinutes().toString().padStart(2, "0")}`;
    }
    else return "";
  }
  let art_html = "";
  for (let i = arts.length - 1; i >= 0; --i) {
    arts[i].type = arts[i].path.split("/")[0];
    if (!checkArt(arts[i])) continue;
    if (count[arts[i].type]) ++count[arts[i].type];
    else count[arts[i].type] = 1;
    art_html += `<div class="card">` +
      `<div class="art-title"><a href="${arts[i].path}">${arts[i].title}</a></div>` +
      `<header class="art-meta">` + (
        `<span class="art-type">${arts[i].type}</span>` +
        `<span class="art-date">${DateToHTML(arts[i].date)}</span>`
      ) + `</header>` +
      `<div class="art-outline">${arts[i].outline}</div>` +
      `</div>`;
  }
  block.innerHTML = art_html;
  let countHtml = "";
  for (let i in count) {
    countHtml += `<div class="two-part"><div>${i}</div><div>${count[i]}</div></div>`;
  }
  artCount.innerHTML = countHtml;
  if (MathJax.typesetPromise) MathJax.typesetPromise(); else MathJax.startup.typeset = true;
}
fetch("list.json").then(r => r.json()).then(s => { arts = s; putArts(); });
/*
function scrollMove(e) {
  let height = document.documentElement.clientHeight;
  let H = document.documentElement.scrollTop;
  if (H < height) {
    top_panel.style.transform = "translateY(" + H / 5 + "px)";
  }
}
document.addEventListener("scroll", scrollMove);*/