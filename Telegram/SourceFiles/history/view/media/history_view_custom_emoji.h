/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "history/view/media/history_view_media_unwrapped.h"

namespace Ui::Text {
struct OnlyCustomEmoji;
} // namespace Ui::Text

namespace Stickers {
struct LargeEmojiImage;
} // namespace Stickers

namespace HistoryView {

class Sticker;

using LargeCustomEmoji = std::variant<
	QString,
	std::unique_ptr<Sticker>,
	std::unique_ptr<Ui::Text::CustomEmoji>>;

class CustomEmoji final : public UnwrappedMedia::Content {
public:
	CustomEmoji(
		not_null<Element*> parent,
		const Ui::Text::OnlyCustomEmoji &emoji);
	~CustomEmoji();

	QSize countOptimalSize() override;
	QSize countCurrentSize(int newWidth) override;
	void draw(
		Painter &p,
		const PaintContext &context,
		const QRect &r) override;

	bool alwaysShowOutTimestamp() override {
		return true;
	}
	bool hasTextForCopy() const override {
		return true;
	}

	bool hasHeavyPart() const override;
	void unloadHeavyPart() override;

private:
	void paintElement(
		Painter &p,
		int x,
		int y,
		LargeCustomEmoji &element,
		const PaintContext &context,
		bool paused);
	void paintSticker(
		Painter &p,
		int x,
		int y,
		not_null<Sticker*> sticker,
		const PaintContext &context,
		bool paused);
	void paintCustom(
		Painter &p,
		int x,
		int y,
		not_null<Ui::Text::CustomEmoji*> emoji,
		const PaintContext &context,
		bool paused);

	const not_null<Element*> _parent;
	std::vector<std::vector<LargeCustomEmoji>> _lines;
	QImage _selectedFrame;
	int _singleSize = 0;
	bool _hasHeavyPart = false;

};

} // namespace HistoryView
